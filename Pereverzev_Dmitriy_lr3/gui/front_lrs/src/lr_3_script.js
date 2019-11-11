
document.getElementById('button_step').disabled = 'disabled';
var ee = document.querySelectorAll("#step_value")[0];
//alert(ee);
ee.innerHTML = '';


function test() {
    var pref_str = document.getElementById('prefix').value.trim().replace(/ /g, '');
    var err = "test";
    var xhr = new XMLHttpRequest();
    xhr.open('POST', '/lr_3_pref', false);
    xhr.setRequestHeader('Content-Type', 'application/json');
    xhr.send(JSON.stringify({ pref_str, err }));
    err = xhr.responseText
    if (err == 0) {
        document.getElementById('prefix').disabled = true;//textarea off
        document.getElementById('button_step').disabled = false;//step on
        document.getElementById('button_go').disabled = true;//go off


        alert("Expression is entered correctly.")
    }
    else {
        alert(`Error found: err#${err}`);
    }
}


function get_str() {
    var pref_str = document.getElementById('prefix').value.trim(),
        flag = document.getElementById('stepbystepflag').checked;
    var xhr = new XMLHttpRequest();
    xhr.open('POST', '/lr_3_pref', false);
    xhr.setRequestHeader('Content-Type', 'application/json')
    if (flag) { pref_str = step(); }
    else { document.getElementById('button_go').disabled = 'disabled'; }

    xhr.send(JSON.stringify({ pref_str, flag }));

    //alert(xhr.responseText); // responseText -- текст     ответа.
    ee.innerHTML += `
    <tr>
        <td>${ee.childElementCount + 1}</td>
        <td>${pref_str}</td>
        <td id='td_${ee.childElementCount + 1}'>${xhr.responseText}</td>

    </tr>
    `;
    if (document.getElementById(`td_${ee.childElementCount}`).innerHTML.trim().search(/ /g) == -1) { document.getElementById('button_step').disabled = true; }

}
function step() {
    if (ee.childElementCount == 0) {
        return document.getElementById('prefix').value.trim();
    }
    else {
        return document.getElementById(`td_${ee.childElementCount}`).innerHTML.trim();
    }
}
