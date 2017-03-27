# cad2xls Python Script
This is a Python script for extracting parameter values from an Assembly (STEP)
file.

The main **GetParameters** class allows the user to create new instances in order to handle
**STEP** files. The CAD file path has to be passed using the **filePath** parameter
belongs to the class **GetParameters**

By default, the class constructor creates an instance using a default path for the
CAD model, this value must be changed modifying the variable **filePath** belongs to
the instance your are dealing with.

**Note:** The FreeCAD path must be changed within the code to your computer
library path, using the variable **sys.path.append**.

---

## Dependencies
* **FreeCAD:** https://www.freecadweb.org/

---
## Executing Python from CMD or Linux terminal
* Navigate to the misccode folder.
* Execute the following commands:

```bash
python
```

```python
import cad2xls
obj = cad2xls.GetParameters()
obj.filePath = 'path_to_stp_file'
obj.loadCAD()
obj.writeTxt()
```
---
## Running the code in Linux

[![Running the code!](https://img.youtube.com/vi/YOUTUBE_VIDEO_ID_HERE/0.jpg)](https://www.youtube.com/watch?v=RIBDlxeZS7M&feature=youtu.be)
