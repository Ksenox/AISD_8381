
//run functioun for read file
document.getElementById('file_in').addEventListener('change', readFile, false);
document.getElementById('string_of_elem').addEventListener('change', string_changed, false);
document.getElementById('find_elem').addEventListener('change', take_elem_for_del, false);
disabled_buttons();

var obj_elems = {
    "elems": [],
    "ind": -1
}

var obj_str = {
    "e_str": "",
    "t_str": ""
}

var obj_tree = {
    "children": [{
        "name": " что-то не то(1)",
        "children": []
    }]
};

var index = 0;
var sorted = "";

//tree style
var margin = { top: 20, right: 90, bottom: 20, left: 0 },
    width = 960 - margin.right - margin.left,
    height = 1000 - margin.top - margin.bottom;

var i = 0,
    duration = 750,
    root;

var tree = d3.layout.tree()
    .size([height, width]);

var diagonal = d3.svg.diagonal()
    .projection(function (d) { return [d.x, d.y]; });

var svg = d3.select(document.getElementById("div_tree")).append("svg")
    .attr("width", width + margin.right + margin.left)
    .attr("height", height + margin.top + margin.bottom)
    .append("g")
    .attr("transform", "translate(" + margin.left + "," + margin.top + ")");





//run functioun for read file


//read file
function readFile(evt) {
    let file = evt.target.files[0];
    let reader = new FileReader();
    reader.onload = (function (theFile) {
        return function (e) {
            var span = document.getElementById("string_of_elem");
            span.value = e.target.result;
            //send_str_of_elems(span.value);
            string_changed();

        };
    })(file);
    reader.readAsText(file);

}



//send str to server
function send_str_of_elems(string_of_elem) {
    let xhr = new XMLHttpRequest();
    xhr.open('POST', '/lr_5_tree', false);
    xhr.setRequestHeader('Content-Type', 'application/json');
    xhr.send(JSON.stringify({ string_of_elem }));
    let err = xhr.responseText;
    debugger
    if (err == 0) {
        alert("all is OK");
        document.getElementById('button_build').disabled = false;
        document.getElementById('button_step').disabled = false;
    }
    else {
        alert("error founded");
    }
}

//button "build"
function step() {
    get_elems(1);
    build();
}

function all_steps() {
    get_elems(obj_elems.elems.length - obj_elems.ind);
    build();
}


function find_and_del(elem_for_del) {
    let xhr = new XMLHttpRequest();
    xhr.open('POST', '/lr_5_tree', false);
    xhr.setRequestHeader('Content-Type', 'application/json');
    xhr.send(JSON.stringify({ elem_for_del }));
    if (obj_str.t_str != xhr.responseText) {
        obj_str.e_str = obj_str.e_str.split(`${elem_for_del} `).join('');
        obj_str.t_str = xhr.responseText;
        build_help();
    }
    else
        alert("element not found");
}

function align() {
    sorted = "";
    sort_arr(obj_str.e_str.slice(0, -1).split(' ').sort())
    obj_str.e_str = sorted;
    build();
}


//help function for
function build() {
    take_tree_str();
    build_help();
}

function build_help() {
    index = 0;
    zeroing_tree();
    build_obj(obj_str.t_str, obj_tree);
    root = obj_tree.children[0];
    root.x0 = height / 2;
    root.y0 = 0;
    update(root);
    if (obj_str.t_str == "_empty") {
        document.getElementById('button_find').disabled = true;
        document.getElementById('button_align').disabled = true;
    }
    else {
        document.getElementById('button_align').disabled = false;
    }
    if (obj_elems.ind >= obj_elems.elems.length - 1) {
        document.getElementById('button_build').disabled = true;
        document.getElementById('button_step').disabled = true;
    }

}

function take_tree_str() {
    let build = obj_str.e_str;
    let xhr = new XMLHttpRequest();
    xhr.open('POST', '/lr_5_tree', false);
    xhr.setRequestHeader('Content-Type', 'application/json');
    xhr.send(JSON.stringify({ build }));
    obj_str.t_str = xhr.responseText;

}

function get_elems(count) {

    obj_str.e_str += obj_elems.elems.slice(obj_elems.ind + 1, obj_elems.ind + 1 + count).join(' ') + ' ';
    obj_elems.ind += count;
}


//build obj of tree
function build_obj(str, obj) {
    var i = 0;
    if (str == "_empty")
        return;
    while (true) {
        if (index == (str.length) - 1)
            return;

        while (str[index] == '(')
            index++;

        if (str[index] == ')') {
            index++;
            return;
        }

        var leaf =
        {
            "name": str[index],
            "children": []
        };
        index++;
        while (str[index] != ')' && str[index] != '(') {
            leaf.name = leaf.name + str[index];
            index++;
        }

        if (obj.children == "empty__") {
            obj = leaf;
        }
        else {
            obj.children[i] = leaf;
            i++;
        }
        build_obj(str, leaf);
    }
}

//painting tree
function update(source) {

    var nodes = tree.nodes(root).reverse(),
        links = tree.links(nodes);

    nodes.forEach(function (d) { d.y = d.depth * 40; });

    var node = svg.selectAll("g.node")
        .data(nodes, function (d) { return d.id || (d.id = ++i); });

    var nodeEnter = node.enter().append("g")
        .attr("class", "node")
        .attr("transform", function (d) {
            return "translate(" + source.x0 + "," + source.y0 + ")";
        })
        .on("click", click);

    nodeEnter.append("circle")
        .attr("r", 1e-6)
        .style("fill", function (d) { return d._children ? "lightsteelblue" : "#fff"; });

    nodeEnter.append("text")
        .attr("x", function (d) { return d.children || d._children ? 13 : -13; })
        .attr("y", -15)
        .attr("dy", ".35em")
        .attr("text-anchor", function (d) { return d.children || d._children ? "end" : "start"; })
        .text(function (d) { return d.text || d.name; })
        .style("fill-opacity", 1e-6);

    var nodeUpdate = node.transition()
        .duration(duration)
        .attr("transform", function (d) { return "translate(" + d.x + "," + d.y + ")"; });

    nodeUpdate.select("circle")
        .attr("r", 10)
        .style("fill", function (d) { return d._children ? "lightsteelblue" : "#fff"; });

    nodeUpdate.select("text")
        .style("fill-opacity", 1);

    var nodeExit = node.exit().transition()
        .duration(duration)
        .attr("transform", function (d) { return "translate(" + source.x + "," + source.y + ")"; })
        .remove();

    nodeExit.select("circle")
        .attr("r", 1e-6);

    nodeExit.select("text")
        .style("fill-opacity", 1e-6);

    var link = svg.selectAll("path.link")
        .data(links, function (d) { return d.target.id; });

    link.enter().insert("path", "g")
        .attr("class", "link")
        .attr("d", function (d) {
            var o = { x: source.x0, y: source.y0 };
            return diagonal({ source: o, target: o });
        });

    link.transition()
        .duration(duration)
        .attr("d", diagonal);

    link.exit().transition()
        .duration(duration)
        .attr("d", function (d) {
            var o = { x: source.x, y: source.y };
            return diagonal({ source: o, target: o });
        })
        .remove();

    nodes.forEach(function (d) {
        d.x0 = d.x;
        d.y0 = d.y;
    });
}

function click(d) {
    /*
    if (d.children) {
        d._children = d.children;
        d.children = null;
    } else {
        d.children = d._children;
        d._children = null;
    }
    */
    find_and_del(d.name);
    update(d);
}

function sort_arr(arr) {
    var center = ((arr.length - 1) / 2 >> 0);

    debugger
    if (arr.length <= 2) {
        for (let i = 0; i < arr.length; i++)
            sorted += arr[i] + ' ';
        return;
    }
    else
        sorted += arr[center] + ' ';
    sort_arr(arr.slice(0, center));
    sort_arr(arr.slice(center + 1, arr.length));


}

function zeroing() {
    zeroing_elems();
    zeroing_tree();
    zeroing_str();
}
function zeroing_elems() {
    obj_elems = {
        "elems": document.getElementById("string_of_elem").value.split(' '),
        "ind": -1
    };
}
function zeroing_str() {
    obj_str = {
        "e_str": "",
        "t_str": ""
    };
}
function zeroing_tree() {
    obj_tree = {
        "children": [{
            "name": " Дерево не задано(ну или что-то не то(1))",
            "children": []
        }]
    };
}

function test_str() {
    let str = document.getElementById("string_of_elem").value;
    str = str.split(' ').filter(onlyUnique).join(' ');
    str = str.replace(/\ \ /g, ' ');
    if (str[str.length - 1] == ' ')
        str = str.slice(0, -1);
    if (str[0] == ' ')
        str = str.slice(1);

    return str;
}

function onlyUnique(value, index, self) {
    return self.indexOf(value) === index;
}

function string_changed() {
    disabled_buttons();
    debugger
    let str = test_str();
    if (document.getElementById("string_of_elem").value == str) {
        alert('The string is accepted');
        document.getElementById('button_build').disabled = false;
        document.getElementById('button_step').disabled = false;
    }
    else {
        if (confirm("The string is an invalid format,\n correct some inaccuracies?")) {
            document.getElementById("string_of_elem").value = str;
            document.getElementById('button_build').disabled = false;
            document.getElementById('button_step').disabled = false;
        }

    }
    debugger
    zeroing();

}

function take_elem_for_del() {
    document.getElementById('button_find').disabled = true;
    let str = document.getElementById("find_elem").value;
    while (str[0] == ' ')
        str = str.slice(1);
    if (str != '') {
        str = str.split(' ')[0];
    }
    else
        return;
    if (str == document.getElementById("find_elem").value) {
        document.getElementById('button_find').disabled = false;
    }
    else if (confirm("The string is an invalid format,\n correct some inaccuracies?")) {
        document.getElementById("find_elem").value = str;
        document.getElementById('button_find').disabled = false;
    }

}

function disabled_buttons() {
    document.getElementById('button_build').disabled = true;
    document.getElementById('button_find').disabled = true;
    document.getElementById('button_step').disabled = true;
    document.getElementById('button_align').disabled = true;
}