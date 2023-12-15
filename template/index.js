const container = document.querySelector('#container');

let current = new Date();
let lastMinutes = current.getMinutes();

let labels = Array.from({ length: dataCount }, (_, i) => beforeMinutes(current, dataCount - i - 1));

function toTimeString(h, m) {
    let hours = h < 10 ? '0' + h : h;
    let minutes = m < 10 ? '0' + m : m;
    return hours + ':' + minutes;
}

function beforeMinutes(current, minutes) {
    let h = current.getHours();
    let m = current.getMinutes();

    m -= minutes;
    while (m < 0) {
        m += 60;
        h--;
    }

    while (h < 0) h += 24;

    return toTimeString(h, m);
}

function add_grid_item(name, unit, data) {
    let item = document.createElement('div');
    item.className = 'grid-item';

    let progress = document.createElement('circle-progress');
    progress.setAttribute('unit', unit);
    progress.setAttribute('title', name);
    progress.setAttribute('value', data[data.length - 1]);

    let graph = document.createElement('line-graph');
    graph.classList.add('hide');
    graph.setAttribute('title', name);

    item.onclick = () => {
        graph.classList.toggle('hide');
        progress.classList.toggle('hide');
        item.classList.toggle('expand');
    }

    item.appendChild(graph);
    item.appendChild(progress);
    container.appendChild(item);

    graph.init(data, labels);
}

json.forEach(item => add_grid_item(item.name, item.unit, item.data));

let curIntervals = [];

function changeProgress(progress, index, value) {
    let current = Number(progress.getAttribute('value'));
    let dr = current > value ? -1 : 1;

    if (curIntervals[index] !== null) {
        clearInterval(curIntervals[index]);
    }

    curIntervals[index] = setInterval(() => {
        if (current == value) {
            clearInterval;
        } else {
            current += dr;
            progress.setAttribute('value', current);
        }
    }, 50);
}

setInterval(() => {
    const currentHours = new Date().getHours();
    const currentMinutes = new Date().getMinutes();

    if (currentMinutes != lastMinutes) {
        fetch('/update')
          .then(response => response.json())
          .then(json => {
            let newLabel = toTimeString(currentHours, lastMinutes);
            document.querySelectorAll('circle-progress').forEach((element, index) => changeProgress(element, index, json[index]));
            document.querySelectorAll('line-graph').forEach((element, index) => element.append(json[index], newLabel));
        });

        lastMinutes = currentMinutes;
    }
}, 1000);