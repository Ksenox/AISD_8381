var str = document.getElementById("tree_str").value;
document.getElementById("button_forest").disabled = true;
document.getElementById("button_take_bin_str").disabled = true;
document.getElementById("button_bin_tree").disabled = true;
document.getElementById("button_bypass_width").disabled = true;
var index = 0;
var obj = {
    "children": [{
        "name": " что-то не то(1)",
        "children": []
    }]
};
var treeData = obj.children;
var obj_bin = {
    "children": [{
        "name": " что-то не то(2)",
        "children": []
    }]
};
var total_quality_tree = 0
var graph = document.getElementById("div_tree");


function build_obj(str, obj) {
    var i = 0;
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




var str_tree = document.getElementById("tree_str").value;

var str = str_tree;

//build_obj(obj);
//treeData = obj.children;




//настройки даиграммы
var margin = { top: 20, right: 90, bottom: 20, left: 0 },
    width = 960 - margin.right - margin.left,
    height = 1000;

var i = 0,
    duration = 750,
    root;
//создаем дерево
var tree = d3.layout.tree()
    .size([height, width]);
//создем контрол, который будет многократно использоваться для визуальной связи между узлами
var diagonal = d3.svg.diagonal()
    .projection(function (d) { return [d.x, d.y]; });
//контейнер (тэг хтмл) в котором будет отрисовка
/*
var svg = d3.select("body").append("svg")
    .attr("width", width + margin.right + margin.left)
    .attr("height", height + margin.top + margin.bottom)
    .append("g")
    .attr("transform", "translate(" + margin.left + "," + margin.top + ")");
    */
//root = treeData[0];
//root.x0 = height / 2;
//root.y0 = 0;

//Run code




d3.select(self.frameElement).style("height", "100%");


function update(source, root) {
    //console.log(treeData);
    console.log(root);
    debugger;
    var svg = d3.select(document.getElementById("div_tree")).append("svg")
        .attr("width", 1080)
        .attr("height", height + margin.top + margin.bottom)
        .append("g")
        .attr("transform", "translate(" + margin.left + "," + margin.top + ")");


    // Compute the new tree layout.
    var nodes = tree.nodes(root).reverse(),
        links = tree.links(nodes);

    // Normalize for fixed-depth.
    nodes.forEach(function (d) { d.y = d.depth * 40; });

    // Update the nodes…
    var node = svg.selectAll("g.node")
        .data(nodes, function (d) { return d.id || (d.id = ++i); });

    // Enter any new nodes at the parent's previous position.
    var nodeEnter = node.enter().append("g")
        .attr("class", "node")
        .attr("transform", function (d) {
            return "translate(" + source.x0 + "," + source.y0 + ")";
        })
        .on("click", click);

    nodeEnter.append("circle")
        .attr("r", 1e-6)
        .style("fill", function (d) { return d._children ? "lightsteelblue" : "#000"; });

    nodeEnter.append("text")
        .attr("x", function (d) { return d.children || d._children ? -13 : 13; })
        .attr("dy", ".35em")
        .attr("text-anchor", function (d) { return d.children || d._children ? "end" : "start"; })
        .text(function (d) { return d.text || d.name; })
        .style("fill-opacity", 1e-6);

    // Transition nodes to their new position.
    var nodeUpdate = node.transition()
        .duration(duration)
        .attr("transform", function (d) { return "translate(" + d.x + "," + d.y + ")"; });

    nodeUpdate.select("circle")
        .attr("r", 10)
        .style("fill", function (d) { return d._children ? "lightsteelblue" : "#fff"; });

    nodeUpdate.select("text")
        .style("fill-opacity", 1);

    // Transition exiting nodes to the parent's new position.
    var nodeExit = node.exit().transition()
        .duration(duration)
        .attr("transform", function (d) { return "translate(" + source.x + "," + source.y + ")"; })
        .remove();

    nodeExit.select("circle")
        .attr("r", 1e-6);

    nodeExit.select("text")
        .style("fill-opacity", 1e-6);

    // Update the links…
    var link = svg.selectAll("path.link")
        .data(links, function (d) { return d.target.id; });

    // Enter any new links at the parent's previous position.
    link.enter().insert("path", "g")
        .attr("class", "link")
        .attr("d", function (d) {
            var o = { x: source.x0, y: source.y0 };
            return diagonal({ source: o, target: o });
        });

    // Transition links to their new position.
    link.transition()
        .duration(duration)
        .attr("d", diagonal);

    // Transition exiting nodes to the parent's new position.
    link.exit().transition()
        .duration(duration)
        .attr("d", function (d) {
            var o = { x: source.x, y: source.y };
            return diagonal({ source: o, target: o });
        })
        .remove();

    // Stash the old positions for transition.
    nodes.forEach(function (d) {
        d.x0 = d.x;
        d.y0 = d.y;
    });
}

// Toggle children on click.
function click(d) {

    debugger;
    if (d.children) {
        d._children = d.children;
        d.children = null;
    } else {
        d.children = d._children;
        d._children = null;
    }
}


function take_tree() {
    str = document.getElementById("tree_str").value;
    console.log("sttr = " + str);
    obj = {
        "children": [{
            "name": " что-то не то",
            "children": []
        }]
    };

    var err = "test";
    err = test_data(str, err);
    if (err != 0) {
        document.getElementById("button_forest").disabled = true;
        document.getElementById("button_take_bin_str").disabled = true;
        return;
    }

    index = 0
    build_obj(str, obj);
    debugger;
    console.log("sttep1");
    root = obj.children[0];
    root.x0 = height / 2;
    root.y0 = 0;
    document.getElementById("button_forest").disabled = false;
    console.log(root);
}

function test_data(str, err) {


    var xhr = new XMLHttpRequest();
    xhr.open('POST', '/lr_4_tree', false);
    xhr.setRequestHeader('Content-Type', 'application/json');

    xhr.send(JSON.stringify({ str, err }));
    err = xhr.responseText;
    if (err == 0) {
        document.getElementById("button_forest").disabled = false;
        document.getElementById("button_take_bin_str").disabled = false;

        alert("Expression is entered correctly.")
    }
    else {
        alert(`Error found: err#${err}`);
    }
    return err;
}

function take_bin_tree() {

    document.getElementById("button_bin_tree").disabled = false;
    document.getElementById("button_bypass_width").disabled = false;


    var bin_str = str;
    var xhr = new XMLHttpRequest();
    xhr.open('POST', '/lr_4_tree', false);
    xhr.setRequestHeader('Content-Type', 'application/json');
    xhr.send(JSON.stringify({ bin_str }));
    bin_str = xhr.responseText;


    index = 0;
    document.getElementById("bin_tree_str").value = bin_str;
    debugger;
    build_obj(bin_str, obj_bin);
    debugger;
    root_bin = obj_bin.children[0];
    root_bin.x0 = height / 2;
    root_bin.y0 = 0;
    document.getElementById("button_forest").disabled = false;


}

function build_graph(obj_of_graph) {
    debugger;
    document.getElementById("div_tree").innerHTML = '';
    for (var i = 0; i < obj_of_graph.children.length; i++) {
        update(root, obj_of_graph.children[i]);
    }
}

function bypass_width() {
    var bypass_width_str = "go";
    var xhr = new XMLHttpRequest();
    xhr.open('POST', '/lr_4_tree', false);
    xhr.setRequestHeader('Content-Type', 'application/json');
    debugger;
    xhr.send(JSON.stringify({ bypass_width_str }));
    bypass_width_str = xhr.responseText;
    debugger;
    document.getElementById("bypass_width_str").value = bypass_width_str;

}