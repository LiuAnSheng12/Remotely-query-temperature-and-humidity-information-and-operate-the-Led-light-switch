//----------------------這裡是主頁面 (/)--------------------
static const char mainPage[] PROGMEM = u8R"(
<!DOCTYPE html>
<html>

<head>
  <style type='text/css'>
    body {
      /*height: 100vh;*/
      background: rgb(0, 122, 170);
      background: -webkit-linear-gradient(left top, rgb(0, 122, 170), white);
      background: -o-linear-gradient(bottom right, rgb(0, 122, 170), white);
      background: -moz-linear-gradient(bottom right, rgb(0, 122, 170), white);
      background: linear-gradient(to bottom right, rgb(0, 122, 170), white);
      font-family: Microsoft JhengHei;
    }

    h1 {

      font-size: 22px;
      color: #ffffff;
      text-align: center;
      margin-top: 30px;
    }

    p.status {
      font-size: 10px;
      color: white;
      background-color: tomato;
      text-align: right;
      margin-top: 30px;
      position: fixed;
      bottom: 0;
      left: 5px;
      padding: 3px;
    }

    p.set {

      margin-bottom: -1px;
      font-size: 13px;
      text-align: left;
      background-color: #09B789;
      color: rgb(240, 240, 240);
      width: 40px;
      padding: 4px;

    }

    div.center {
      margin: auto;
      width: 80%;
      border-top: 2px solid white;
      border-bottom: 2px solid white;
      padding: 10px;
      text-align: left;
    }

    div.setArea {
      border: 1px solid white;
      padding: 10px;
      text-align: center;
    }

    div.testArea {
      border: 1px solid white;
      padding: 10px;
      text-align: center;
    }

    div.edArea {
      border: 1px solid white;
      padding: 10px;
      text-align: center;
    }

    input.text_1 {

      margin: 5px;
      width: 15%;
      border: 3px;
      padding: 15px;
      font-size: 15px;
    }

    select {
      margin: auto;
      width: 100%;

      padding: 15px;
    }

    .button {
      border: none;
      padding: 13px 10px;
      margin: 4px 2px;
      font-size: 15px;
      font-family: Microsoft JhengHei;
      text-align: center;
      text-decoration: none;
      display: inline-block;
      cursor: pointer;
      background-color: #555555;
      border-radius: 4px;
      color: white;
    }

    .button:hover {
      background-color: tomato;
      color: white;
    }

    textarea {
      text-align: center;
      font-size: 12px;
      width: 100%;
    }
  </style>
  <meta charset='UTF-8'>
  <meta name='viewport' content='width=device-width, initial-scale=1.0'>
  <title>旗標科技手機遙控跳舞機器人</title>
  <script>
    var iOS = /iPad|iPhone|iPod/.test(navigator.userAgent) && !window.MSStream;
    var allSteps = [
      { val: '0', txt: '0.停止舞步' },
      { val: 'A', txt: 'A.左右踮腳扭身 1 次 (全程 32 拍)' },
      { val: 'B', txt: 'B.踮左腳尖 1 次' },
      { val: 'C', txt: 'C.踮右腳尖 1 次' },
      { val: 'D', txt: 'D.左扭右扭向前' },
      { val: 'E', txt: 'E.原地滑步踮腳尖 1 次 (全程 31 拍)' },
      { val: 'F', txt: 'F.月球漫步向左' },
      { val: 'G', txt: 'G.月球漫步向右' },
      { val: 'H', txt: 'H.小跳步' },
      { val: 'I', txt: 'I.酒醉搖晃 1 次' },
      { val: 'J', txt: 'J.左傾踢右腳 1 次' },
      { val: 'K', txt: 'K.右傾踢左腳 1 次' },
      { val: 'L', txt: 'L.前進' },
      { val: 'M', txt: 'M.後退' },
      { val: 'N', txt: 'N.逐漸踮腳 1 次' },
      { val: 'O', txt: 'O.無重力狀態 1 次' },
      { val: 'P', txt: 'P.左右斜側身踮腳' },
      { val: 'Q', txt: 'Q.踮腳向左 1 次' },
      { val: 'R', txt: 'R.向內扭腳滑步' },
      { val: 'S', txt: 'S.上下踮腳' },
      { val: 'T', txt: 'T.抬右腿' },
      { val: 'U', txt: 'U.左右搖擺' },
      { val: 'V', txt: 'V.蹺腳尖' },
      { val: 'W', txt: 'W.蹺腳尖向內扭' },
      { val: 'X', txt: 'X.小跑步往前' },
      { val: 'Y', txt: 'Y.暫停 1 次' },
    ];

    var stepOptions;
    var step;
    var timesField;
    var beatsField;
    var stepsText;
    var status;
    var choreography;
    var fileLoad;

    function initAll() {
      stepOptions = document.getElementById('stepOptions');
      step = document.getElementById('step');
      timesField = document.getElementById('timesField');
      beatsField = document.getElementById('beatsField');
      stepsText = document.getElementById('stepsText');
      status = document.getElementById('status');
      choreography = document.getElementById('choreography');
      fileLoad = document.getElementById('load');

      var newOption;
      timesField.hidden = true;
      beatsField.hidden = true;
      stepsText.hidden = !iOS;
      for (var i = 0; i < allSteps.length; i++) {
        newOption = document.createElement('option');
        newOption.text = allSteps[i].txt;
        newOption.value = allSteps[i].val;
        stepOptions.add(newOption);
        newOption = document.createElement('option');
        newOption.text = allSteps[i].txt;
        newOption.value = allSteps[i].val;
        step.add(newOption);
      }
    }

    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
      if (this.readyState == 4 && this.status == 200) {
        status.innerHTML = '已經送出';
      }
      else {
        status.innerHTML = '無法送出';
      }
    };

    function startDance(id) {
      var steps = '';

      status.innerHTML = '送出中...';

      if (id == 'setBPM') {
        var bpmStr = document.getElementById('bpm').value;
        var bpm = parseInt(bpmStr);
        if (isNaN(bpm)) {
          status.innerHTML = '請輸入整數...';
        }
        else {
          xhttp.open('GET', 'dance?bpm=' + bpm, true);
          xhttp.send();
        }
        return;
      }
      else if (id == 'dance') {
        for (var i = 0; i < choreography.options.length; i++) {
          steps += choreography.options[i].value + '\n';
        }
        xhttp.open('POST', 'dance', true);
        xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
        xhttp.send('steps=' + steps);
      }
      else if (id == 'test') {
        steps = step.value;
        xhttp.open('GET', 'dance?type=' + steps, true);
        xhttp.send();
      }
      else if (id == 'stop') {
        steps = '0,1,1';
        xhttp.open('POST', 'dance', true);
        xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
        xhttp.send('steps=' + steps);
      }
    }

    function setField() {
      var stepType = stepOptions.options[stepOptions.selectedIndex].value;
      var stepText = stepOptions.options[stepOptions.selectedIndex].text;
      timesField.hidden = false;
      beatsField.hidden = false;
      if (stepType == 'A' || stepType == 'E' || stepType == '0') {
        timesField.hidden = true;
        beatsField.hidden = true;
      }
      else if (stepText.indexOf('次') != -1) {
        timesField.hidden = true;
      }
    }

    function addStep() {
      var newStep = document.createElement('OPTION');
      var stepType = stepOptions.options[stepOptions.selectedIndex].value;
      var stepText = stepOptions.options[stepOptions.selectedIndex].text;
      if (stepType == 'A' || stepType == 'E' || stepType == '0') {
        newStep.text = stepText;
      }
      else if (stepText.indexOf('次') != -1) {
        newStep.text = stepText + ' ' +
          beats.value + ' 拍';
      }
      else {
        newStep.text = stepText + ' ' +
          times.value + ' 次, 每次 ' +
          beats.value + ' 拍';
      }
      newStep.value =
        stepType + ',' +
        times.value + ',' +
        beats.value;
      newStep.selected = true;
      choreography.add(newStep, choreography.selectedIndex + 1);
    }

    function removeStep() {
      var currIndex = choreography.selectedIndex;
      choreography.remove(currIndex);
      choreography.selectedIndex = (currIndex > 0) ? (currIndex - 1) : 0;
    }

    function gotoSetting() {
      location.href = '/setting';
    }

    function download(data, filename, type) {
      var file = new Blob([data], { type: type });
      if (window.navigator.msSaveOrOpenBlob) // IE10+
        window.navigator.msSaveOrOpenBlob(file, filename);
      else {
        var a = document.createElement('a'),
          url = URL.createObjectURL(file);
        a.href = url;
        a.download = filename;
        document.body.appendChild(a);
        a.click();
        setTimeout(function () {
          document.body.removeChild(a);
          window.URL.revokeObjectURL(url);
        }, 0);
      }
    }

    function startSave() {
      var steps = [];
      for (var i = 0; i < choreography.options.length; i++) {
        var currStep = {};
        currStep.val = choreography.options[i].value;
        currStep.txt = choreography.options[i].text;
        steps.push(currStep);
      }
      if(iOS) {
        stepsText.value = JSON.stringify(steps);
      }
      else {
        download(JSON.stringify(steps), 'steps.json', 'text/plain');
      }
    }

    function startLoad() {
      if(iOS) {
        var stepsInput = window.prompt('請輸入編舞資料：', '');
        if(stepsInput != null) {
          stepsText.value = stepsInput;
          updateChoreography(stepsInput);
        }
      }
      else {
        fileLoad.click();
      }
    }

    function updateChoreography(stepsJSON) {
      var steps = JSON.parse(stepsJSON);
      if (steps) {
        while (choreography.length > 0) {
          choreography.remove(0);
        }
        for (var i = 0; i < steps.length; i++) {
          var newOption = new Option();
          newOption.text = steps[i].txt;
          newOption.value = steps[i].val;
          choreography.add(newOption);
        }
        choreography.selectedIndex = 0;
      }
    }

    function goLoad() {
      var reader = new FileReader();

      reader.addEventListener('loadend', function () {
        updateChoreography(reader.result);
        stepsText.value = stepsInput;
      }, false);
      reader.readAsText(fileLoad.files[0], 'utf8');
    }

    function clearSteps() {
      while (choreography.length > 0) {
        choreography.remove(0);
      }
      choreography.selectedIndex = 0;
    }
  </script>
</head>

<body onload='initAll()'>
  <h1>旗標科技手機遙控跳舞機器人</h1>
  <div class='center'>
    <p class='set'>設定區</p>
    <div class='setArea'>
      <input class='text_1' type='number' id='bpm' value='121' />
      <input class='button button1' type='button' id='setBPM' value=' ♫ 設定每分鐘拍數' onClick='startDance(this.id)' /><br>
      <input class='button button1' style='width: 100%' type='button' value=' ✎ 進馬達調校頁面' onClick='gotoSetting()'>
      </button>
    </div>
    <p class='set'>測試區</p>
    <div class='testArea'>
      <input class='button' style='width: 100%;font-size: 15px;' type='button' id='test' value=' ☑ 測試舞步' onClick='startDance(this.id)' />
      <select id='step'></select>
    </div>
    <p class='set'>編舞區</p>
    <div class='edArea'>
      <select id='stepOptions' onchange='setField()'></select>
      <span id='timesField'>
        <input class='text_1' type='number' id='times' value='1' maxlength='3' size='3' /> 次</span>
      <span id='beatsField'>每次
        <input class='text_1' type='number' id='beats' value='1' size='3' /> 拍</span>
    </div>
    <div class='edArea'>
      <input class='button button1' style='width: 30%' type='button' id='addStep' value=' ＋ 新增 ' onClick='addStep()' />
      <input class='button button1' style='width: 30%' type='button' id='removeStep' value=' － 刪除 ' onClick='removeStep()' />
      <input class='button button1' style='width: 30%' type='button' id='clear' value=' × 清除' onClick='clearSteps()' />
      <select id='choreography' size='4'></select>
      <input class='button button1' style='width: 46%' type='button' id='dance' value=' ▷ 開始' onClick='startDance(this.id)' />
      <input class='button button1' style='width: 46%' type='button' id='stop' value=' □ 停止 ' onClick='startDance(this.id)' />
      <br>
      <input class='button button1' style='width: 46%' type='button' id='goSave' value=' ↓ 下載編舞' onClick='startSave()' />
      <input class='button button1' style='width: 46%' type='button' id='goLoad' value=' ↑ 上傳舊檔' onClick='startLoad()' />
      <input class='button' style='display:none' type='file' id='load' onChange='goLoad()' />
      <textarea rows='4' readonly id='stepsText'></textarea>
    </div>
    <p class='status' id='status'>機器人狀態</p>
  </div>
</body>

</html>
)";

//----------------------這裡是錯誤路徑頁面--------------------
static const char errorPage[] PROGMEM= u8R"(
<!DOCTYPE html>
<html>
<style type='text/css'>
    body{
        /*height: 100vh;*/
        background: tomato;   
        font-family: Microsoft JhengHei;
      }
      div.all{
        border: 5px solid white;
        text-align: center;
        padding: 30px;
        margin-top: 35%;
      }
      h1{
        color: rgb(240,240,240);

      }
    button {
        border: none;
        padding: 13px 15px;
        margin: 4px 2px;
        font-size: 15px;
        text-align: center;
        text-decoration: none;
        display: inline-block;
        cursor: pointer;
        background-color: #F6EC00;
        border-radius: 4px;
        color: tomato;
        font-weight: 900;
        font-size: 15px;
    }

    button:hover {
        background-color: #555555; 
        color: white;
    }

</style>
<head>
  <meta charset='UTF-8'> 
  <meta name='viewport' content='width=device-width, initial-scale=1.0'>
  <script>
    function backToHome() {
      location.href = '/';
    }
  </script>
<title>旗標科技手機遙控跳舞機器人--路徑錯誤</title>
</head>
<body>
  <div class='all'>
    <h1>網址錯了, 我不知道該怎麼處理？</h1>
    <button onClick='backToHome()'>回主頁</button>
  </div>
</body>
</html>
)";

//---------------------這裡是設定頁面 (/setting)  
static const char settingPage[] PROGMEM= u8R"(
  <!DOCTYPE html>
<html>

<head>
  <style type='text/css'>
    body {
      /*height: 100vh;*/
      background: rgb(0, 122, 170);
      background: -webkit-linear-gradient(left top, rgb(0, 122, 170), white);
      background: -o-linear-gradient(bottom right, rgb(0, 122, 170), white);
      background: -moz-linear-gradient(bottom right, rgb(0, 122, 170), white);
      background: linear-gradient(to bottom right, rgb(0, 122, 170), white);
      font-family: Microsoft JhengHei;
    }

    h1 {

      font-size: 22px;
      color: #ffffff;
      text-align: center;
      margin-top: 30px;
    }

    p.status {
      font-size: 10px;
      color: white;
      background-color: tomato;
      text-align: right;
      margin-top: 30px;
      position: fixed;
      bottom: 0;
      left: 5px;
      padding: 3px;
    }

    p.set {

      margin-bottom: -1px;
      font-size: 13px;
      text-align: left;
      background-color: #09B789;
      color: rgb(240, 240, 240);
      width: 40px;
      padding: 4px;

    }

    div.center {
      margin: auto;
      width: 80%;
      border-top: 2px solid white;
      border-bottom: 2px solid white;
      padding: 10px;
      text-align: left;
    }

    div.setArea {
      border: 1px solid white;
      padding: 10px;
      text-align: center;
    }

    .button {
      border: none;
      padding: 13px 10px;
      margin: 4px 2px;
      font-size: 15px;
      font-family: Microsoft JhengHei;
      text-align: center;
      text-decoration: none;
      display: inline-block;
      cursor: pointer;
      background-color: #555555;
      border-radius: 4px;
      color: white;
    }

    .button:hover {
      background-color: tomato;
      color: white;
    }
  </style>
  <meta charset='UTF-8'>
  <meta name='viewport' content='width=device-width, initial-scale=1.0'>
  <title>旗標科技跳舞機器人調校</title>
  <script>
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById('status').innerHTML = '已經送出';
      }
      else if (this.readyState == 4 && this.status == 303) {
        document.getElementById('status').innerHTML = '已經送出';
        location.href = '/';
      }
      else {
        document.getElementById('status').innerHTML = '無法送出';
      }
    };

    function adjRobot(action) {
      xhttp.open('GET', 'adj?type=' + action, true);
      xhttp.send();
    }

    function initAll() {
      adjRobot(0);
    }
  </script>
</head>

<body onload='initAll()'>
  <h1>旗標科技跳舞機器人馬達調校</h1>
  <div class='center'>
    <!-- 設定區 -->
    <p class='set'>設定區</p>
    <div class='setArea'>
      <input class='button button1' style='width: 46%' type='button' id='adjLLMinus' value='左腳逆時針轉' onClick='adjRobot(1)' />
      <input class='button button1' style='width: 46%' type='button' id='adjRLMinus' value='右腳逆時針轉' onClick='adjRobot(3)' /><br>
      <input class='button button1' style='width: 46%' type='button' id='adjLLAdd' value='左腳順時針轉' onClick='adjRobot(2)' />
      <input class='button button1' style='width: 46%' type='button' id='adjRLAdd' value='右腳順時針轉' onClick='adjRobot(4)' />
    </div>
    <div class='setArea'>
      <input class='button button1' style='width: 46%' type='button' id='adjLFMinus' value='左腳掌往上轉' onClick='adjRobot(5)' />
      <input class='button button1' style='width: 46%' type='button' id='adjRFPlus' value='右腳掌往上轉' onClick='adjRobot(8)' /><br>
      <input class='button button1' style='width: 46%' type='button' id='adjLFPlus' value='左腳掌往下轉' onClick='adjRobot(6)' />
      <input class='button button1' style='width: 46%' type='button' id='adjRFMinus' value='右腳掌往下轉' onClick='adjRobot(7)' />
    </div>
    <div class='setArea'>
      <input class='button button1' style='width: 46%' type='button' id='adjSave' value='儲存調校值' onClick='adjRobot(9)' />
      <input class='button button1' style='width: 46%' type='button' id='adjRestore' value='套用儲存值' onClick='adjRobot(10)' />
    </div>
    <!-- 設定區 -->
    <p class='status' id='status'>機器人狀態</p>
  </div>
</body>

</html>
)";

//---------以下這一行不要刪除, 這可以讓網頁資料儲存在程式區, 節省記憶體--------------
#define WEBPAGE_IN_PROGMEM