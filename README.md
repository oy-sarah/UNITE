# UNITE
This is the replicate package of UNITE and a fault localization demo used UNITE for nanoxml_v1, fault 1.
UNITE is used for representing the trace from both global and local contexts with influential semantics for FL(Fault Localization).
# Usage
## Requirements:
windows 10
gcc 3.3.1
python 3.7

## For Subject Programs:
### Description of Documents
In folder of subjectPrograms, there are 19 subjuct programs. For smaller spectrum files in each subject program, we uploaded them.
For large spectrum files, we provide the a download link.
Take nanoxml_v1/nanoxml_v1_f1 as an example:
there are componentinfo.txt, covMatrix.txt and error.txt, which are spectrum files of program nanoxml_v1 under the test cases.
Other files are computing files for UNITE.
### Slicing tools
We use JSlice(http://jslice.sourceforge.net/) and Javaslicer(https://github.com/hammacher/javaslicer/) for slicing Java programs, and WET(http://wet.cs.ucr.edu/) for slicing C Programs.
### Run UNITE
run GlobalAndLocalContextsCompute.bat
### Get Result
covMatrix1.txt

## For the fault localization demo used UNITE:
### Description of Documents
In folder of faultLocalizationDemo:
1.source code:StdXMLParser.java
2.buggy line:297 if (! XMLUtil.checkLiteral(this.reader, '&', this.entityResolver,"<OCTYPE")) { 
3.correct format:if (! XMLUtil.checkLiteral(this.reader, '&', this.entityResolver,"OCTYPE")) { 
4.In folder analysePro, there are componentinfo.txt, covMatrix.txt and error.txt, which are spectrum files of program StdXMLParser.java under 206 test cases.
### Run demo
run getResult.bat
### Get Result
result.txt(fault localization result with rank and Exam value)

