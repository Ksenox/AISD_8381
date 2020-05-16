

document.getElementById('from_num').addEventListener('change', function () { check_num("from_num") }, false);
document.getElementById('to_num').addEventListener('change', function () { check_num("to_num") }, false);
document.getElementById('q_leafs').addEventListener('change', function () { check_num("q_leafs") }, false);
document.getElementById('q_tests').addEventListener('change', function () { check_num("q_tests") }, false);

function take_table() {
    let obj_out = {
        "from": document.getElementById("from_num").value,
        "to": document.getElementById("to_num").value
    };
    let flag = false;
    if (obj_out.from == '') {
        obj_out.from = 1;
        flag = true;
    }
    if (obj_out.to == '') {
        obj_out.to = obj_out.from + 999;
        flag = true;
    }
    if (obj_out.from / 1 - obj_out.to / 1 > 999) {
        obj_out.to = obj_out.from + 999;
        flag = true;
    }


    flag ? alert(`Only first 1000 items will be shown, starting from ${obj_out.from}`) : NaN;
    let xhr = new XMLHttpRequest();
    xhr.open('POST', '/cw_table', true);
    xhr.onreadystatechange = function () {
        if (xhr.readyState == 4) {
            if (xhr.status == 200) {
                let str_data = xhr.responseText;
                build_table(JSON.parse(str_data));
            }
        }
    };
    xhr.setRequestHeader('Content-Type', 'application/json');
    xhr.send(JSON.stringify({ obj_out }));

}


function build_table(arr_data) {

    debugger
    let table = '';
    for (let i = 0; i < arr_data.length; i++) {
        if (arr_data[i].itemset.length > 83)
            arr_data[i].itemset = arr_data[i].itemset.slice(0, 83) + "..."
        table +=
            `<tr id="row_${i + 1}">
                <td>${arr_data[i].id}</td>
                <td>${arr_data[i].itemset}</td>
                <td>${arr_data[i].time}</td>
                <td>${arr_data[i].steps}</td>
            </tr>
            `
    }
    document.getElementById("table_body").innerHTML = table;

}

function check_num(id) {
    let num = document.getElementById(id).value;
    if (num != '') {
        num = parseInt(num);
        if (isNaN(num))
            num = '';
    }
    if (num != document.getElementById(id).value) {
        document.getElementById(id).value = num;
        alert("String changed");
    }

}

function check_fields() {
    let err = "";
    if (document.getElementById("q_leafs").value == "") {
        err += "Check value of 'Quantity of leafs in tree'\n";
    }
    if (document.getElementById("q_tests").value == "") {
        err += "Check value of 'Quantity of tests'\n";
    }
    if (document.getElementById("distrib").value == "null") {
        err += "Choose available value of distributing\n";
    }
    if (err != "") {
        alert(err);
        return true
    }
    else return false
}


function gen_data() {
    if (check_fields())
        return;
    let obj_gen = {
        "len": parseInt(document.getElementById("q_leafs").value),
        "num": parseInt(document.getElementById("q_tests").value),
        "flag": document.getElementById("distrib").value
    }

    let xhr = new XMLHttpRequest();
    xhr.open('POST', '/cw_table', true);
    xhr.onreadystatechange = function () {
        if (xhr.readyState == 4) {
            if (xhr.status == 200) {
                let ret = xhr.responseText;
                if (ret == "done")
                    alert("Data generated");
            }
        }
    };
    xhr.setRequestHeader('Content-Type', 'application/json');
    xhr.send(JSON.stringify({ obj_gen }));

}
