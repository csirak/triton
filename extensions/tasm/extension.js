"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.activate = exports.TasmFormatter = void 0;
var vscode_1 = require("vscode");
var TasmFormatter = /** @class */ (function () {
    function TasmFormatter() {
    }
    TasmFormatter.prototype.provideDocumentFormattingEdits = function (document, options, token) {
        var text = document.getText();
        var formattedText = this.formatText(text);
        // Split the original text and the formatted text into lines
        var originalLines = text.split("\n");
        var formattedLines = formattedText.split("\n");
        var edits = [];
        // Ensure that both arrays have the same length
        var length = Math.min(originalLines.length, formattedLines.length);
        // Compare the original and formatted lines to identify the changes
        for (var i = 0; i < length; i++) {
            if (originalLines[i] !== formattedLines[i]) {
                // If a line has changed, create a TextEdit to replace the original line with the formatted line
                edits.push(vscode_1.TextEdit.replace(new vscode_1.Range(i, 0, i + 1, 0), // Replace the entire line
                formattedLines[i] // Use the formatted line
                ));
            }
        }
        return edits;
    };
    TasmFormatter.prototype.formatText = function (text) {
        // Split the code into lines
        var lines = text.split("\n");
        // Process each line and apply your formatting logic
        for (var i = 0; i < lines.length; i++) {
            // Check if the line contains a label (ends with a colon)
            if (lines[i].trim().endsWith(":")) {
                // Add a newline after the label
                lines.splice(i + 1, 0, ""); // Add an empty line after the label
                i++; // Move to the next line
            }
        }
        // Join the lines back together with newlines to reconstruct the formatted code
        var formattedText = lines.join("\n").trim();
        return formattedText;
    };
    return TasmFormatter;
}());
exports.TasmFormatter = TasmFormatter;
function activate(context) { }
exports.activate = activate;
