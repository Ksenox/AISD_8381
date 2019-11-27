
document.getElementById("button_tree").disabled = true;
document.getElementById("button_find").disabled = true;


var obj = {
    "children": [{
        "name": " что-то не то(1)",
        "children": []
    }]
};
var index = 0;
var sstr;


var margin = { top: 20, right: 90, bottom: 20, left: 0 },
    width = 960 - margin.right - margin.left,
    height = 500 - margin.top - margin.bottom;

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

function take_tree_str() {
    var string_of_elem = document.getElementById("string_of_elem").value;
    debugger
    sstr = '';
    sort_str(string_of_elem.split(' ').sort((a, b) => { return a - b }));
    string_of_elem = sstr;
    debugger
    var xhr = new XMLHttpRequest();
    xhr.open('POST', '/lr_5_tree', false);
    xhr.setRequestHeader('Content-Type', 'application/json');
    debugger
    xhr.send(JSON.stringify({ string_of_elem }));
    var err = xhr.responseText;
    if (err != 0)
        alert(`Error: num#${err}`);
    else
        document.getElementById("button_tree").disabled = false;

}

function take_tree() {
    //document.getElementById("button_tree").disabled = true;
    var build = "go";
    var xhr = new XMLHttpRequest();
    xhr.open('POST', '/lr_5_tree', false);
    xhr.setRequestHeader('Content-Type', 'application/json');
    debugger
    xhr.send(JSON.stringify({ build }));
    var string_tree = xhr.responseText;
    build_tree(string_tree);

}

function build_tree(string_tree) {
    obj = {
        "children": [{
            "name": "Дерево пустоe (Но есть шанс, что что-то не работает(1))",
            "children": []
        }]
    };
    index = 0;
    build_obj(string_tree, obj);

    root = obj.children[0];
    root.x0 = height / 2;
    root.y0 = 0;
    tree_style();
    update(root);
    debugger;
}

function tree_style() {

    document.getElementById("div_tree").innerHTML = '';

    margin = { top: 20, right: 90, bottom: 20, left: 0 };
    width = 960 - margin.right - margin.left;
    height = 500 - margin.top - margin.bottom;

    i = 0;
    duration = 750;
    root;

    tree = d3.layout.tree()
        .size([height, width]);

    diagonal = d3.svg.diagonal()
        .projection(function (d) { return [d.x, d.y]; });

    svg = d3.select(document.getElementById("div_tree")).append("svg")
        .attr("width", width + margin.right + margin.left)
        .attr("height", height + margin.top + margin.bottom)
        .append("g")
        .attr("transform", "translate(" + margin.left + "," + margin.top + ")");

    d3.select(self.frameElement).style("height", "500px");
}

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
        .attr("x", function (d) { return d.children || d._children ? -13 : 13; })
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
    find_and_del(d.name);
}


function find_and_del(elem_for_del) {
    var xhr = new XMLHttpRequest();
    xhr.open('POST', '/lr_5_tree', false);
    xhr.setRequestHeader('Content-Type', 'application/json');
    debugger
    xhr.send(JSON.stringify({ elem_for_del }));
    var string_tree = xhr.responseText;
    build_tree(string_tree)

}


document.getElementById('file_in').addEventListener('change', readFile, false);

function readFile(evt) {
    var file = evt.target.files[0];
    var reader = new FileReader();
    reader.onload = (function (theFile) {
        return function (e) {
            var span = document.getElementById("string_of_elem");
            span.value = e.target.result;
        };
    })(file);
    reader.readAsText(file);
}

document.getElementById('find_elem').addEventListener('change', test_value, false);

function test_value() {
    document.getElementById("button_find").disabled = true;

    if (!isNaN(document.getElementById('find_elem').value / 1)) {
        document.getElementById("button_find").disabled = false;
    }

}

function sort_str(arr) {
    var center = ((arr.length - 1) / 2 >> 0);

    debugger
    if (arr.length <= 2) {
        for (let i = 0; i < arr.length; i++)
            sstr += arr[i] + ' ';
        return;
    }
    else
        sstr += arr[center] + ' ';
    sort_str(arr.slice(0, center));
    sort_str(arr.slice(center + 1, arr.length));


}