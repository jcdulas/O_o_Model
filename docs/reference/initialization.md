# 2. Initialization

## Executive records

Use `[executive]` for the solution sequence, file assignments and executive statements. A record starts with its neutral name. Field positions and accepted options belong to that statement. [Text model sections](../model-format.md#sections)

| Purpose | Format | Example | Interpretation |
| --- | --- | --- | --- |
| Choose an analysis | `SolutionSequence;sequence` | `SolutionSequence;LinearStatics` | Selects linear statics for this model |
| Record a time limit | `TimeLimit;minutes` | `TimeLimit;15` | Stores the requested limit in the model |
| Associate a file with a unit | `FileAssignment;assignment;FileUnit=n` | `FileAssignment;RESULTS='tie.bin';FileUnit=22` | Records the external path and logical unit |

### File management

Use `Include;parts/rod.oos` to read another text file at that position. Use `FileAssignment` to declare an external unit. Opening an include reads its model records immediately, whereas a unit assignment describes a resource for a consumer. [Include paths](../model-format.md#includes-and-parts)

### Output control

Put model titles and result requests in `[case]`. For example, `DisplacementOutput;All` asks for displacements at all nodes. Writing a model archive from the Reader stores the model. Result datasets enter an archive when the application supplies result tables. [Case control](case-control.md) · [Archive layout](../archive-format.md#layout)

### Memory management

The application owns the loaded model and query tables. In JavaScript, release a finished query and deck with `delete()`. In Python the objects follow Python ownership. When inspecting a large model, request the columns needed for the operation. [Model lifetime and batch input](../model-construction.md#performance-validation-and-lifetime)

### Program control

Set the solution once, then define subcases that select its data. A stored solution or execution directive describes the job for the consuming program. Reading the file alone performs model I/O. [Case commands A–Z](case-commands.md)
