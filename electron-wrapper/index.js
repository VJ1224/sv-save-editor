const { app, BrowserWindow } = require('electron') 

function createWindow() { 
    let window = new BrowserWindow({ 
        width: 1024, 
        height: 768, 
    });

    window.loadURL('http://142.93.214.88:18080/');

    window.on('closed', () => { 
        window = null
    });

    window.webContents.on('new-window', (event, url) => { 
        event.preventDefault() 
        window.loadURL(url) 
    });
}

app.disableHardwareAcceleration();
app.on('ready', createWindow) ;
