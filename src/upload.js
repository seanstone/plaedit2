document.getElementById("fileinput").addEventListener('change', uploadFile);

function uploadFile()
{
    var fileToLoad = document.getElementById("fileinput").files[0];
    if (!fileToLoad) alert("Please select file to upload!");
    else {
        var fileReader = new FileReader();
        fileReader.onload = function(fileLoadedEvent){
            Module['FS_createDataFile'](".", fileToLoad.name, fileReader.result, true, true);
            console.log(fileToLoad.name + " uploaded");
            Module.cwrap('readPLA', 'number', ['string'])(fileToLoad.name);
        };
        fileReader.readAsBinaryString(fileToLoad);
    }
}
