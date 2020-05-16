
document.getElementById('file_in').addEventListener('change', readFile, false);
document.getElementById('string_of_elem').addEventListener('change', string_changed, false);
disabled_buttons(true);



var obj_elems = {
    "elems": [],
    "ind": 0
}

var obj_str = {
    "elems_str": "",
    "tree_str": ""
}

var obj_tree = {
    "children": [{
        "name": " что-то не то(1)",
        "children": []
    }]
};

var index = 0;


//tree style

var margin = { top: 20, right: 0, bottom: 20, left: document.body.offsetWidth * 0.1 },
    width = document.body.offsetWidth * 0.9,
    height = 1000 - margin.top - margin.bottom;

var i = 0,
    duration = 750,
    root;

var tree = d3.layout.tree()
    .size([height, width]);

var diagonal = d3.svg.diagonal()
    .projection(function (d) { return [d.x, d.y]; });

var svg = d3.select(document.getElementById("div_tree")).append("svg")
    .attr("width", width)
    .attr("height", height + margin.top + margin.bottom)
    .append("g")
    .attr("transform", "translate(" + margin.left + "," + margin.top + ")");


//read file
function readFile(evt) {
    let file = evt.target.files[0];
    let reader = new FileReader();
    reader.onload = (function (theFile) {
        return function (e) {
            var span = document.getElementById("string_of_elem");
            span.value = e.target.result;
            string_changed();

        };
    })(file);
    reader.readAsText(file);

}


function string_changed() {
    disabled_buttons(true);
    debugger
    let str = test_str();
    if (document.getElementById("string_of_elem").value == str) {
        alert('The string is accepted');
        disabled_buttons(false);
        send_flag();
    }
    else {
        if (confirm("The string is an invalid format,\n correct some inaccuracies?")) {
            document.getElementById("string_of_elem").value = str;
            send_flag();
            disabled_buttons(false);
        }
    }
    zeroing();
}

function send_flag() {
    let xhr = new XMLHttpRequest();
    xhr.open('POST', '/cw_tree', false);
    xhr.setRequestHeader('Content-Type', 'application/json');
    debugger
    xhr.send(JSON.stringify({ "text_edited": true }));
    console.log(xhr.responseText);
}

function onlyUnique(value, index, self) {
    return self.indexOf(value) === index;
}

function test_str() {
    let str = document.getElementById("string_of_elem").value;
    str = str.split(' ').filter(onlyUnique).join(' ').replace(/\n/g, ' ');
    str = str.replace(/\ \ /g, ' ');
    if (str[str.length - 1] == ' ')
        str = str.slice(0, -1);
    if (str[0] == ' ')
        str = str.slice(1);

    return str;
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
    if (d.children) {
        d._children = d.children;
        d.children = null;
    } else {
        d.children = d._children;
        d._children = null;
    }
    update(d);
}

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

function disabled_buttons(t_f) {
    document.getElementById('button_build').disabled = t_f;
    document.getElementById('button_step').disabled = t_f;

}

function zeroing() {
    zeroing_elems();
    zeroing_tree();
    zeroing_str();
}
function zeroing_tree() {
    obj_tree = {
        "children": [{
            "name": " Дерево пустое(или что-то не то(1))",
            "children": []
        }]
    };
}
function zeroing_elems() {
    obj_elems = {
        "elems": document.getElementById("string_of_elem").value.split(' '),
        "ind": 0
    }
}
function zeroing_str() {
    obj_str = {
        "elems_str": "",
        "tree_str": ""
    }
}

function all_steps() {
    build(obj_elems.elems.length - obj_elems.ind);
    obj_elems.ind = obj_elems.elems.length;
    disabled_buttons(true);

}
function step() {
    build(1);
    obj_elems.ind++;




}

function build(quantity) {
    take_tree_str(quantity);
    build_help();
}

function take_tree_str(quantity) {
    let build = obj_elems.elems.slice(obj_elems.ind, obj_elems.ind + quantity);
    obj_str.elems_str += ` ${build.join(' ')}`;
    let xhr = new XMLHttpRequest();
    xhr.open('POST', '/cw_tree', false);
    xhr.setRequestHeader('Content-Type', 'application/json');
    xhr.send(JSON.stringify({ build }));
    obj_str.t_str = xhr.responseText;

}

function build_help() {
    index = 0;
    zeroing_tree();
    build_obj(obj_str.t_str, obj_tree);
    root = obj_tree.children[0];
    root.x0 = height / 2;
    root.y0 = 0;
    update(root);

    if (obj_elems.ind >= obj_elems.elems.length - 1) {
        disabled_buttons(true);
    }

}

