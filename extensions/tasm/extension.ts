import {
  ExtensionContext,
  languages,
  TextDocument,
  FormattingOptions,
  CancellationToken,
  TextEdit,
  Range,
} from "vscode";

export class TasmFormatter {
  provideDocumentFormattingEdits(
    document: TextDocument,
    options: FormattingOptions,
    token: CancellationToken
  ): TextEdit[] {
    const text = document.getText();
    const formattedText = this.formatText(text);

    // Split the original text and the formatted text into lines
    const originalLines = text.split("\n");
    const formattedLines = formattedText.split("\n");

    const edits: TextEdit[] = [];

    // Ensure that both arrays have the same length
    const length = Math.min(originalLines.length, formattedLines.length);

    // Compare the original and formatted lines to identify the changes
    for (let i = 0; i < length; i++) {
      if (originalLines[i] !== formattedLines[i]) {
        // If a line has changed, create a TextEdit to replace the original line with the formatted line
        edits.push(
          TextEdit.replace(
            new Range(i, 0, i + 1, 0), // Replace the entire line
            formattedLines[i] // Use the formatted line
          )
        );
      }
    }

    return edits;
  }

  formatText(text: string): string {
    // Split the code into lines
    const lines = text.split("\n");

    // Process each line and apply your formatting logic
    for (let i = 0; i < lines.length; i++) {
      // Check if the line contains a label (ends with a colon)
      if (lines[i].trim().endsWith(":")) {
        // Add a newline after the label
        lines.splice(i + 1, 0, ""); // Add an empty line after the label
        i++; // Move to the next line
      }
    }

    // Join the lines back together with newlines to reconstruct the formatted code
    const formattedText = lines.join("\n").trim();

    return formattedText;
  }
}

export function activate(context: ExtensionContext) {}
