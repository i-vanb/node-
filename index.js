const express = require('express');
const multer = require('multer');
const upload = multer({ dest: 'uploads/' })
const fs = require('fs');
const handlebars = require('express-handlebars')
    .create({defaultLayout: 'main'});

const app = express();

app.engine('handlebars', handlebars.engine);
app.set('view engine', 'handlebars');

const port = 3000;

let mae
let rmape
let error

app.use(express.static(__dirname + '/public'));

app.get('/', (req, res) => {
    res.render('home', {mae, rmape});
});

app.post('/check', upload.single('loadedFile'), (req, res)=> {
    let userFile = req.file;
    const fileName = userFile.filename
    console.log(userFile);

    if(!userFile) {
        error = 'Файл не загружен'
    } else {
        fs.writeFile("node.bat",
            `cd metrics\ng++ -o rmape.exe rmape.cpp\ng++ -o mae.exe mae.cpp\nrmape.exe ../result/ans.csv ../uploads/${fileName} ../result/ind.csv\nmae.exe ../result/ans.csv ../uploads/${fileName} ../result/ind.csv`,
            function(error){
                if(error) throw error;
                const { spawn } = require('child_process');
                const result = []

                const bat = spawn('cmd.exe', [`/c`, 'node.bat']);

                bat.stdout.on('data', (data) => {
                    if(data.toString().startsWith('ok')) {
                        const str = data.toString().replace('ok:','').replace('\r\n','')
                        result.push(parseFloat(str))
                    }
                    console.log(data.toString());
                });

                bat.stderr.on('data', (data) => {
                    console.error(data.toString());
                });

                bat.on('exit', (code) => {
                    fs.unlinkSync("node.bat")
                    console.log(result)
                    rmape = result[0]
                    mae = result[1]
                    console.log(`Child exited with code ${code}`);
                    error = null
                    fs.unlink(fileName, ()=>console.log(fileName + ' file is removed!'))
                    res.redirect('/')
                });
            }
        );
    }
})

app.use((req, res, next)=>{
    res.status(404);
    res.render('404');
});

app.use((req, res, next)=>{
    res.status(500);
    res.render('500');
});

app.listen(port, () => {
    console.log(`Example app listening at http://localhost:${port}`)
})
