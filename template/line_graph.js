class LineGraph extends HTMLElement {
    constructor() {
        super();
        this.data = [];
        this.labels = [];
        this.attachShadow({ mode: 'open' });
    }

    init(data, labels) {
        data.slice(-60).forEach(item => this.data.push(item));
        labels.slice(-60).forEach(item => this.labels.push(item));
        this.chart.update();
    }

    append(data, label) {
        this.data.push(data);
        this.labels.push(label);

        if (this.data.length > 60) {
            this.data.shift();
            this.labels.shift();
        }

        this.chart.update();
    }

    connectedCallback() {
        let title = this.getAttribute('title');

        this.shadowRoot.innerHTML = `
        <style>
            a {
                color: inherit;
            }
            
            .graph {
                width: 720px;
                display: block;
                background: #0b131b;
                color: #ffffff;
                border-radius: 8px;
                padding: 8px;
            }
            
            .title {
                display: block;
                word-break: keep-all;
                font-weight: 800;
                font-size: 1.5em;
                letter-spacing: -0.02ch;
                margin-block: 0.83em;
                margin-inline: 0px;
                margin: 0px;
            }
        </style>
        <div class="graph">
            <h2 class="title">${title}</h2>
            <div style="display: block; height: 8px;"></div>
            <div style="height: 400px; width: auto;">
                <canvas id="canvas"></canvas>
            </div>
        </div>`;

        const ctx = this.shadowRoot.querySelector('#canvas').getContext('2d');

        this.chart = new Chart(ctx, {
            type: 'line',
            data: {
                labels: this.labels,
                datasets: [{
                    lineTension: 0,
                    data: this.data,
                    borderColor: "rgb(39, 226, 164)",
                }]
            },
            options: {
                responsive: true,
                maintainAspectRatio: false,
                plugins: { legend: { display: false } },
                scales: {
                    x: { ticks: { color: 'white', maxTicksLimit: 15 } },
                    y: { ticks: { color: 'white' } },
                }
            },
        });
    }
}

customElements.define('line-graph', LineGraph);