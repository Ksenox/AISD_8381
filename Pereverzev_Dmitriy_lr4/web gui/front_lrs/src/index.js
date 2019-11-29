
var ee = document.querySelectorAll("#step_value")[0];
ee.innerHTML = '';

function get_str() {
    document.getElementById('prefix').disabled = 'disabled';
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
    if (document.getElementById(`td_${ee.childElementCount}`).innerHTML.trim().length < 2) { document.getElementById('button_go').disabled = 'disabled'; }

}
function step() {
    if (ee.childElementCount == 0) {
        return document.getElementById('prefix').value.trim();
    }
    else {
        return document.getElementById(`td_${ee.childElementCount}`).innerHTML;
    }
}