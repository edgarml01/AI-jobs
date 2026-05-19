import * as vscode from 'vscode';
import * as http from 'http';

// ============================================================================
// CONFIGURACIÓN DE LA EXTENSIÓN Y SERVIDOR
// ============================================================================

// Dirección del servidor Flask local
const SERVER_URL = 'http://127.0.0.1:5000/predict';

// Parámetros de generación por defecto
const DEFAULT_NUM_CHARS = 50;
const DEFAULT_TEMPERATURE = 0.7;

/**
 * Interfaz para la respuesta esperada del servidor Flask
 */
interface PredictResponse {
    success?: boolean;
    prompt?: string;
    completion?: string;
    full_text?: string;
    error?: string;
}

// ============================================================================
// CLIENTE HTTP NATIVO (Sin dependencias externas)
// ============================================================================

/**
 * Realiza una petición POST HTTP nativa al servidor Flask local.
 * Utiliza el módulo 'http' de Node.js para garantizar compatibilidad sin librerías externas.
 */
function solicitarPrediccion(prompt: string, numChars: number, temperature: number): Promise<string> {
    return new Promise((resolve, reject) => {
        const payload = JSON.stringify({
            prompt: prompt,
            num_chars: numChars,
            temperature: temperature
        });

        const urlObj = new URL(SERVER_URL);
        const options: http.RequestOptions = {
            hostname: urlObj.hostname,
            port: urlObj.port,
            path: urlObj.pathname,
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
                'Content-Length': Buffer.byteLength(payload)
            },
            timeout: 3000 // Tiempo de espera máximo de 3 segundos
        };

        const req = http.request(options, (res) => {
            let data = '';

            res.on('data', (chunk) => {
                data += chunk;
            });

            res.on('end', () => {
                if (res.statusCode && res.statusCode >= 200 && res.statusCode < 300) {
                    try {
                        const jsonResponse = JSON.parse(data) as PredictResponse;
                        if (jsonResponse.success && jsonResponse.completion) {
                            resolve(jsonResponse.completion);
                        } else {
                            reject(new Error(jsonResponse.error || 'Respuesta inválida del servidor.'));
                        }
                    } catch (err) {
                        reject(new Error('Error al parsear el JSON del servidor.'));
                    }
                } else {
                    reject(new Error(`Error del servidor: Código HTTP ${res.statusCode}`));
                }
            });
        });

        req.on('error', (err) => {
            reject(new Error(`No se pudo conectar al servidor Flask (${SERVER_URL}). Asegúrate de que server.py esté en ejecución.`));
        });

        req.on('timeout', () => {
            req.destroy();
            reject(new Error('Tiempo de espera agotado al conectar con el servidor Flask.'));
        });

        req.write(payload);
        req.end();
    });
}

// ============================================================================
// PROVEEDOR DE AUTOCOMPLETADO (CompletionItemProvider)
// ============================================================================

class CCodeCompletionProvider implements vscode.CompletionItemProvider {
    
    public async provideCompletionItems(
        document: vscode.TextDocument,
        position: vscode.Position,
        token: vscode.CancellationToken,
        context: vscode.CompletionContext
    ): Promise<vscode.CompletionItem[] | undefined> {
        
        // 1. Obtener el contexto antes del cursor
        // Tomamos hasta 5 líneas antes de la posición actual del cursor
        // (El modelo RNN de Keras fue entrenado con secuencias de longitud 100)
        const startLine = Math.max(0, position.line - 5);
        const startPosition = new vscode.Position(startLine, 0);
        const rangeObj = new vscode.Range(startPosition, position);
        const prompt = document.getText(rangeObj);

        if (!prompt || prompt.trim().length === 0) {
            return undefined;
        }

        try {
            // 2. Leer configuraciones de la extensión (si existen en settings.json) o usar defaults
            const config = vscode.workspace.getConfiguration('cAutocompleteRnn');
            const numChars = config.get<number>('maxChars', DEFAULT_NUM_CHARS);
            const temperature = config.get<number>('temperature', DEFAULT_TEMPERATURE);

            // 3. Solicitar la predicción al servidor Flask
            const completionText = await solicitarPrediccion(prompt, numChars, temperature);

            if (!completionText || token.isCancellationRequested) {
                return undefined;
            }

            // 4. Construir el ítem de autocompletado para VSCode
            const completionItem = new vscode.CompletionItem(completionText, vscode.CompletionItemKind.Snippet);
            
            // Insertar exactamente el texto predicho
            completionItem.insertText = completionText;
            completionItem.detail = "🤖 AI Autocomplete (RNN)";
            
            // Documentación enriquecida en Markdown
            const doc = new vscode.MarkdownString();
            doc.appendMarkdown(`### Predicción de Red Neuronal (RNN)\n`);
            doc.appendCodeblock(completionText, 'c');
            doc.appendMarkdown(`\n*Generado localmente vía Flask (Temp: ${temperature})*`);
            completionItem.documentation = doc;

            // Orden de prioridad para que aparezca primero en la lista
            completionItem.sortText = "0000_rnn_autocomplete";

            return [completionItem];

        } catch (error: any) {
            // Mostrar mensaje de advertencia silencioso en la barra de estado o consola
            console.warn('CCodeCompletionProvider Error:', error.message);
            return undefined;
        }
    }
}

// ============================================================================
// CICLO DE VIDA DE LA EXTENSIÓN (Activate / Deactivate)
// ============================================================================

export function activate(context: vscode.ExtensionContext) {
    console.log('¡La extensión "c-autocomplete-rnn" ha sido activada!');

    // Registrar el proveedor para archivos de lenguaje C ('c')
    const cProvider = vscode.languages.registerCompletionItemProvider(
        { scheme: 'file', language: 'c' },
        new CCodeCompletionProvider(),
        '.', '_', ' ', '(', '{' // Caracteres que disparan el autocompletado
    );

    context.subscriptions.push(cProvider);

    // Comando opcional para verificar el estado de conexión con el servidor
    const checkStatusCmd = vscode.commands.registerCommand('cAutocompleteRnn.checkStatus', async () => {
        try {
            await solicitarPrediccion("int ", 5, 0.5);
            vscode.window.showInformationMessage('¡Conexión exitosa con el servidor Flask local (RNN)!');
        } catch (err: any) {
            vscode.window.showErrorMessage(`Error de conexión con el servidor Flask: ${err.message}`);
        }
    });

    context.subscriptions.push(checkStatusCmd);
}

export function deactivate() {
    console.log('La extensión "c-autocomplete-rnn" ha sido desactivada.');
}
