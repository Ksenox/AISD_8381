


var data_now = {
    "average_case": [],
    "worst_case": []

};

function take_data(data_to_table) {
    let arr_data;
    let xhr = new XMLHttpRequest();
    xhr.open('POST', '/cw_graph_dop', true);
    xhr.onreadystatechange = function () {
        if (xhr.readyState == 4) {
            if (xhr.status == 200) {
                debugger
                arr_data = JSON.parse(xhr.responseText);
                choose_table(data_to_table, arr_data.sort((a, b) => {
                    return a.number_of_leaves - b.number_of_leaves;
                }));
            }
        }
    };
    xhr.setRequestHeader('Content-Type', 'application/json');
    xhr.send(JSON.stringify({ data_to_table }));

}

function choose_table(data_to_table, arr_data) {
    if (data_to_table == "average_case") {
        data_now.average_case = arr_data;
        update_table(arr_data, 2);
    }
    else if (data_to_table == "worst_case") {
        data_now.worst_case = arr_data;
        update_table(arr_data, 3);
    }
}



function update_table(arr_data, num_table) {
    debugger;
    let table = '';
    for (let i = 0; i < arr_data.length; i++) {
        table +=
            `<tr id="row_${i + 1}">
                <td>${arr_data[i].id}</td>
                <td>${arr_data[i].number_of_tests}</td>
                <td>${arr_data[i].number_of_leaves}</td>
                <td>${arr_data[i].time_2}</td>
                </tr>
            `
        // <td>${arr_data[i].steps}</td>

    }
    debugger
    document.getElementById(`table_body_${num_table}`).innerHTML = table;
}

// arr_data to dataReady
function form() {
    let arr1 = [];
    for (let i = 0; i < data_now.average_case.length; i++)
        arr1[i] = {
            // "steps": data_now.average_case[i].steps,
            "time_2": data_now.average_case[i].time_2,
            "num": data_now.average_case[i].number_of_leaves
        }
    let arr2 = [];
    for (let i = 0; i < data_now.worst_case.length; i++)
        arr2[i] = {
            // "steps": data_now.worst_case[i].steps,
            "time_2": data_now.worst_case[i].time_2,
            "num": data_now.worst_case[i].number_of_leaves
        }


    return [
        {
            "name": "Average",
            "values": arr1
        },
        {
            "name": "Worst",
            "values": arr2
        }

    ];
}


var margin = { top: 10, right: 10, bottom: 30, left: document.getElementById("my_dataviz").offsetWidth * 0.08 },
    width = document.getElementById("my_dataviz").offsetWidth * 0.92 - margin.left - margin.right,
    height = 360 - margin.top - margin.bottom;

var svg;

//Read the data
function rebuild(id) {
    debugger;

    document.getElementsByTagName("svg")[0] = '';

    let max_value_y = Math.max.apply(Math, [
        Math.max.apply(Math, data_now.average_case.map(function (o) {
            return id == 1 ? o.time_2 : o.steps;
        })),
        Math.max.apply(Math, data_now.worst_case.map(function (o) {
            return id == 1 ? o.time_2 : o.steps;
        }))
    ]);
    console.log(max_value_y);

    let max_value_x = Math.max.apply(Math, [
        Math.max.apply(Math, data_now.average_case.map(function (o) {
            return o.number_of_leaves;
        })),
        Math.max.apply(Math, data_now.worst_case.map(function (o) {
            return o.number_of_leaves;
        }))
    ]);
    console.log(max_value_x);

    if (document.getElementById(`graph_${id}`))
        document.getElementById(`graph_${id}`).remove();

    svg = d3.select(document.getElementById("my_dataviz"))
        .append("svg")
        .attr("id", `graph_${id}`)
        .attr("width", width + margin.left + margin.right)
        .attr("height", height + margin.top + margin.bottom)
        .append("g")
        .attr("transform",
            "translate(" + margin.left + "," + margin.top + ")");

    debugger;

    let allGroup = ["Average", "Worst"];


    debugger
    var dataReady = form();
    console.log(dataReady);

    var myColor = d3.scaleOrdinal()
        .domain(allGroup)
        .range(d3.schemeSet2);

    var x = d3.scaleLinear()
        .domain([0, max_value_x * 1.1])
        .range([0, width]);
    svg.append("g")
        .attr("transform", "translate(0," + height + ")")
        .call(d3.axisBottom(x));

    var y = d3.scaleLinear()
        .domain([0, max_value_y * 1.1])
        .range([height, 0]);
    svg.append("g")
        .call(d3.axisLeft(y));

    var line = d3.line()
        .x(function (d) { return x(+d.num) })
        .y(function (d) { return y(+id == 1 ? d.time_2 : d.steps) })
    svg.selectAll("myLines")
        .data(dataReady)
        .enter()
        .append("path")
        .attr("class", function (d) { return d.name })
        .attr("d", function (d) { return line(d.values) })
        .attr("stroke", function (d) { return myColor(d.name) })
        .style("stroke-width", 4)
        .style("fill", "none")


    svg
        .selectAll("myDots")
        .data(dataReady)
        .enter()
        .append('g')
        .style("fill", function (d) { return myColor(d.name) })
        .attr("class", function (d) { return d.name })
        .selectAll("myPoints")
        .data(function (d) { return d.values })
        .enter()
        .append("circle")
        .attr("cx", function (d) { return x(d.num) })
        .attr("cy", function (d) { return y(id == 1 ? d.time_2 : d.steps) })
        .attr("r", 5)
        .attr("stroke", "white")

    svg
        .selectAll("myLabels")
        .data(dataReady)
        .enter()
        .append('g')
        .append("text")
        .attr("class", function (d) { return d.name })
        .datum(function (d) { return { name: d.name, value: d.values[d.values.length - 1] }; })
        .attr("transform", function (d) { return "translate(" + x(d.value.num) + "," + y(id == 1 ? d.value.time_2 : d.value.steps) + ")"; })
        .attr("x", 12)
        .text(function (d) { return d.name; })
        .style("fill", function (d) { return myColor(d.name) })
        .style("font-size", 15)


    svg
        .selectAll("myLegend")
        .data(dataReady)
        .enter()
        .append('g')
        .append("text")
        .attr('x', function (d, i) { return 30 + i * 60 })
        .attr('y', 10)
        .text(function (d) { return d.name; })
        .style("fill", function (d) { return myColor(d.name) })
        .style("font-size", 15)
        .on("click", function (d) {
            currentOpacity = d3.selectAll("." + d.name).style("opacity")
            d3.selectAll("." + d.name).transition().style("opacity", currentOpacity == 1 ? 0 : 1)

        })
};

take_data('average_case');
take_data('worst_case');
setTimeout((a, b) => { rebuild(1); }, 100, 1);



