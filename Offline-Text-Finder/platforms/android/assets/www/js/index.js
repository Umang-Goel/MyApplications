/*
 The MIT License (MIT)

 Copyright (c) 2015 FOSSASIA
 Copyright (c) 2015 Tymon Radzik

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

//
// FUNCTIONS DECLARATIONS
//

document.addEventListener('deviceready', devReady, false);

var storage = window.localStorage;

function keyExists(key) {
    return (storage.getItem(key) !== null);
}

function getCallerId() { //returns e.g. "index.html" or "dir.html"
    //alert(document.location.href);
    console.log(document.location.href);
    if(document.location.href.indexOf("index.html") != -1)
        return "index.html";
    if(document.location.href.indexOf("directory_picker.html") != -1)
        return "directory_picker.html";
    //alert(document.location.href.split('/'));
    return document.location.href.split('/')[8];
}

function openUrl(url) {
    window.open(url, "_system");
}

function fail(e) {
    window.alert(e.target.error.code);
}

// Directory picker specific functions

var picker_currDir = null;
var picker_parrentDir = null;

function picker_fromPath(name) {
    console.log("In from path");
    picker_currDir.getDirectory(name, {create: false}, function(dir){picker_listDir(dir);}, fail);
}

function picker_fromAbsolute(path) {
    window.resolveLocalFileSystemURL = window.resolveLocalFileSystemURL || window.webkitResolveLocalFileSystemURL;
    window.resolveLocalFileSystemURL(path, function(dir){picker_listDir(dir);}, fail);
}

function picker_listParent() {
    picker_listDir(picker_parrentDir);
}

function picker_selectDir() {
    storage.setItem("searchPath", picker_currDir.toURL());
    window.location.href = "index.html";
}

function picker_listDir(dirEntry) {
    if(!dirEntry.isDirectory) return;
    document.getElementById("currDir").innerHTML = dirEntry.toURL();

    $('.preload_bg').fadeIn();

    picker_currDir = dirEntry;

    var dirReader = dirEntry.createReader();
    dirReader.readEntries(function(rows) {
        document.getElementById("listDiv").innerHTML  = "<ul class=\"list-group\">";
        dirEntry.getParent(function(dirName){
            document.getElementById("listDiv").innerHTML += "<li class=\"list-group-item\"><a onclick='picker_listParent()'>[GO UP]</a></li>";
            picker_parrentDir = dirName;
        },fail);
        if(!rows.length)
            document.getElementById("listDiv").innerHTML += "<li class=\"list-group-item\"><a onclick='picker_listParent()'>Directory is Empty</a></li>";
       
       for(var i = 0; i < rows.length; i++) {
           var row = rows[i];
            if(row.isDirectory) {
                document.getElementById("listDiv").innerHTML += "<li class=\"list-group-item\"><a onclick=\"picker_fromPath('" + row.name + "')\">" + row.name + "</a></li>";
            }
           else if(row.isFile) {
                document.getElementById("listDiv").innerHTML += "<li class=\"list-group-item\">" + row.name + "</li>";
            }
       }
        $('.preload_bg').fadeOut();
        document.getElementById('listDiv').innerHTML += "</ul>";
    });

}

//

//---
//---
//---

//Search module functions

var curr_categories = [];
var found_occurs = [];
var query ="";


function search_getCategories() {
    if(getCallerId() != "index.html" || !keyExists("searchPath")) return;
    $('.preload_bg').fadeIn();
    $('#categoriesUl input:checked').each(function() {
        curr_categories.push($(this).val());
    });
    query = $('#searchP').val();
    console.log("query is "+query);
    found_occurs = [];
    document.getElementById("resultsUl").innerHTML = " No Documents found !!";


    search_folder(storage.getItem("searchPath"));
    
    //for(i=0;i<found_occurs.length;i++)
    //	document.getElementById("resultsUl").innerHTML += "<li class=\"list-group-item\">" + found_occurs[i].name + "</li>";

    $('#showCategories').hide();
    $('#fileContent').hide();
    $('#showResults').show();
    $('.preload_bg').fadeOut();
}

function search_folder(dirAbsolutePath) {
    
    window.resolveLocalFileSystemURL(dirAbsolutePath, function(dirEntry) {
            if(!dirEntry.isDirectory) return;
            var dirReader = dirEntry.createReader();
            if(dirAbsolutePath == storage.getItem("searchPath")) {
                dirReader.readEntries(function(rows) {
                    for(var i = 0; i < rows.length; i++) {
                        var row = rows[i];
                        if(row.isDirectory) {
                            if($.inArray(row.name, curr_categories) != -1) search_folder(row.toURL());
                        }
                        else if (row.isFile && $.inArray("[top]", curr_categories) != -1) {
                            search_file(row);
                        }
                    }
                }, fail);
            }
            else {
                dirReader.readEntries(function(rows) {
                    for(var i = 0; i < rows.length; i++) {
                        var row = rows[i];
                        if(row.isDirectory) search_folder(row.toURL());
                        else if (row.isFile)
                        {
                            search_file(row);
                        } 
                    }
                }, fail);
            }
    }, fail);
}

function search_file(fileEntry)
{
    fileEntry.file(function(file) {
        //alert('name '+fileEntry.name);
        var fileReader = new FileReader();
        fileReader.onloadend = function (evt) {
            //console.log(evt.target.result);
            if(typeof evt.target.result == "string"){
	            docWords = evt.target.result.toLowerCase().split(/[^a-zA-z0-9]/);	//extract list of words from file content
	            queryWords = query.toLowerCase().split(/[^a-zA-z0-9]/);	//extract list of words from given query
	            console.log('doc length '+docWords.length);
	            for(i=0;i<queryWords.length;i++)
	            {
	                console.log("word is "+queryWords[i]);
	            	if($.inArray(queryWords[i], docWords) != -1)
	            	{
	                    if(found_occurs.length == 0)
	                    {
	                        document.getElementById("resultsUl").innerHTML = "<li class=\"list-group-item\" id=\"" + fileEntry.toURL() + "\">" + fileEntry.name + "</li>";
	                        found_occurs.push(fileEntry.name);
	                    }
	            		else if($.inArray(fileEntry.name, found_occurs) == -1)
	                    {
	                        console.log('added');
	                        document.getElementById("resultsUl").innerHTML += "<li class=\"list-group-item\" id=\"" + fileEntry.toURL() + "\">" + fileEntry.name + "</li>";
	            			found_occurs.push(fileEntry.name);
	                    }
	            	}
	            }
	        }
        };
        fileReader.onerror = function (evt) {
	    };
        fileReader.readAsText(file);
    }, fail);
}

function writeToFile(dirEntry,fileName,data)
{
    /*
    
     data -> list of strings
     fileName -> name of the file which is to be written
     dirEntry -> Directory Entry Object where it is to be written
     
    */
    
    dirEntry.getFile(fileName, {create:true}, function(fileEntry) {
        fileEntry.createWriter(function(fileWriter) {
          fileWriter.onwriteend = function(e) {
            console.log('Write completed.');
          };
          fileWriter.onerror = function(e) {
            console.log('Write failed: ' + e.toString());
          };
          // Create a new Blob and write it to log.txt.
          var blob = new Blob(data, {type: 'text/plain'});
          fileWriter.write(blob);
        }, fail);
      }, fail);
}

function createFile(dirEntry)
{
    dirEntry.getFile('Julius Caesar.txt', {create: true, exclusive: true}, function(fileEntry) {
        }, fail);
    console.log('f1 done');
    dirEntry.getFile('Romeo and Juliet.txt', {create: true, exclusive: true}, function(fileEntry) {
        }, fail);
    console.log('f2 done');
    dirEntry.getFile('The Tempest.txt', {create: true, exclusive: true}, function(fileEntry) {
        }, fail);
    console.log('f3 done');
    
    writeToFile(dirEntry,'Julius Caesar.txt',['Julius Caesar book.' ,'this is line 1','line 2.']);
    writeToFile(dirEntry,'Romeo and Juliet.txt',['Romeo and Juliet book.', 'this is line 1','line 2.']);
    writeToFile(dirEntry,'The Tempest.txt',['the Tempest book', 'this is line 1','line 2.']);
}

var path = 'music1/genres1/jazz1/';

function createDir(rootDirEntry, folders) {
  // Throw out './' or '/' and move on to prevent something like '/foo/.//bar'.
    alert('in create dir');
  if (folders[0] == '.' || folders[0] == '') {
    folders = folders.slice(1);
  }
  rootDirEntry.getDirectory(folders[0], {create: true}, function(dirEntry) {
    // Recursively add the new subfolder (if we still have another to create).
      alert('here');
    if (folders.length) {
        console.log('folder name' + folders[0]);
      createDir(dirEntry, folders.slice(1));
    }
  }, fail);
}

function getCategories() {
    if(!keyExists("searchPath") || getCallerId() != "index.html")return;
    $('.preload_bg').fadeIn();
    window.resolveLocalFileSystemURL(storage.getItem("searchPath"), function(dirLoc){
        if(!dirLoc.isDirectory)return;
       var catReader = dirLoc.createReader();
        catReader.readEntries(function(categories){
            document.getElementById("categoriesUl").innerHTML += "<li class=\"list-group-item\"><input type=\"checkbox\" checked=\"checked\" id='[top]' value='[top]' name='[top]'>[top]</input></li>";
           for(var i = 0; i < categories.length; i++) {
               var category = categories[i];
               if(category.isDirectory) {
                   document.getElementById("categoriesUl").innerHTML += "<li class=\"list-group-item\"><input type=\"checkbox\" checked=\"checked\" id='" + category.name + "' value='" + category.name + "' name='" + category.name + "'>" + category.name + "</input></li>";
               }
           }
            $('.preload_bg').fadeOut();
        });
    }, fail);
}

//
// END OF FUNCTIONS DECLARATIONS
//

$('#resultsUl a').click(function(){
    filePath = $(this).attr('id');
    window.resolveLocalFileSystemURL(filePath, function(fileEntry) {
        fileEntry.file(function(file) {
            //alert('name '+fileEntry.name);
            var fileReader = new FileReader();
            fileReader.onloadend = function (evt) {
                console.log(evt.target.result);
                fileText = evt.target.result;
                docWords = evt.target.result.split(/[^a-zA-z0-9]/);	//extract list of words from file content
                console.log('doc length '+docWords.length);
                result = '<p>';
                pos = 0;
                for(i=0;i<docWords.length;i++)
                {
                    result += docWords[i];
                    if(pos < fileText.length && fileText.charAt(pos) == '\n')
                        result +='</p><p>';
                    else
                        result += fileText.charAt(pos);
                    pos += docWords[i].length;
                }
                document.getElementById("fileContent").innerHTML = result;
                 $('#showCategories').hide();
                 $('#fileContent').show();
                 $('#showResults').hide();
            };
            fileReader.readAsText(file);
        }, fail);
    });
});

function devReady() {
    console.log("DEVICE IS READY")
    
    get_started();
    
    basedir = cordova.file.externalRootDirectory;

}

// window.requestFileSystem  = window.requestFileSystem || window.webkitRequestFileSystem;
//     window.resolveLocalFileSystemURL = window.resolveLocalFileSystemURL || window.webkitResolveLocalFileSystemURL;
//window.storageInfo = window.storageInfo || window.webkitStorageInfo;
function get_started(){
	$('#showResults').hide();
switch (getCallerId()) {
    case "index.html":
        if(!keyExists("searchPath")) {
            $('.preload_bg').fadeOut();
            
	    //alert('in index.html');
	    window.resolveLocalFileSystemURL(cordova.file.externalRootDirectory,function(fs){
		fs.getDirectory("OfflineDemoFiles", {create: true, exclusive: true});
	    });
            //document.getElementById("searchBtn").disabled = true;
        $('#showResults').hide();
            document.getElementById("errorMsg").innerHTML = "Path isn't specified";
            break;
        }
        else {
            $('.preload_bg').fadeOut();
            /*window.storageInfo.requestQuota(PERSISTENT, 1024*1024, function(grantedBytes) {
	            console.log('before func call');
	            window.requestFileSystem(PERSISTENT, grantedBytes, function (fileSystem) {
	                console.log('inside func');
	                //picker_listDir(fileSystem.root); // Load root of phone's filesystem
	                createDir(fileSystem.root,path.split('/'));
	            }, fail);
	            }, function(e) {
	                console.log('Error', e); 
        	});*/
            getCategories();
           
           $('#showResults').hide();
            document.getElementById("dirPath").innerHTML = storage.getItem("searchPath");
            document.getElementById("errorMsg").innerHTML = "Phrase length should be longer than 2 and shorter than 65 characters";
        }
        break;
    case "directory_picker.html":
        $('.preload_bg').fadeOut();
        window.resolveLocalFileSystemURL(cordova.file.externalRootDirectory,function(fs){
		picker_listDir(fs); // Load root of phone's filesystem
	});

        /*window.requestFileSystem  = window.requestFileSystem || window.webkitRequestFileSystem;
        alert(window.PERSISTENT);
        window.requestFileSystem(1, 0, function (fileSystem) {picker_fromAbsolute("file:///");}, fail);
            window.requestFileSystem(window.PERSISTENT, 5*1024*1024, 0, function (fileSystem) {
                picker_fromAbsolute("file:///"); // Load root of phone's filesystem
            }, fail);*/
        
}
}
