class CircleProgress extends HTMLElement {
    constructor() {
        super();
        this.attachShadow({ mode: 'open' });
    }

    connectedCallback() {
        this.render();
    }

    static get observedAttributes() {
        return ['value'];
    }

    attributeChangedCallback() {
        this.render();
    }

    render() {
        let unit = this.getAttribute('unit');
        let title = this.getAttribute('title');
        let value = this.getAttribute('value');

        this.shadowRoot.innerHTML = `
        <style>
            * {
                box-sizing: border-box;
            }

            .skill {
                width: 160px;
                height: 160px;
                position: relative;
                pointer-events: none;
            }
            
            .outer {
                width: 160px;
                height: 160px;
                padding: 20px;
                border-radius: 50%;
                box-shadow: 6px 6px 10px -1px rgba(0, 0, 0, 0.15),
                            -6px -6px 10px -1px rgba(0, 0, 0, 0.7)
            }
            
            .inner {
                width: 120px;
                height: 120px;
                border-radius: 50%;
                display: flex;
                align-items: center;
                justify-content: center;
                box-shadow: inset 4px 4px 6px -1px rgba(0, 0, 0, 0.2),
                            inset -4px -4px 6px -1px rgba(0, 0, 0, 0.7),
                            -0.5px -0.5px 0px rgba(0, 0, 0, 1),
                            0.5px 0.5px 0px rgba(0, 0, 0, 0.15),
                            0px 12px 10px -10px rgba(0, 0, 0, 0.05);
            }
            
            #number {
                font-weight: 700px;
                color: white;
            }
            
            circle {
                fill: none;
                stroke: url(#GradientColor);
                stroke-width: 20px;
                stroke-dasharray: 440;
                stroke-dashoffset: calc((100 - var(--value)) * 440 / 100);
            }
            
            svg {
                position: absolute;
                top: 0;
                left: 0;
            }
        </style>
        <div>
            <div style="text-align: center; color: white">${title}</div>
            <div style="display: block; height: 8px;"></div>
            <div class="skill">
                <div class="outer">
                    <div class="inner">
                        <div id="number">${value}${unit}</div>
                    </div>
                </div>
                <svg xmlns="http://www.w3.org/2000/svg" version="1.1" width="160px" height="160px">
                    <defs>
                        <linearGradient id="GradientColor">
                            <stop offset="0%" stop-color="#e91e63" />
                            <stop offset="100%" stop-color="#673ab7" />
                        </linearGradient>
                    </defs>
                    <circle cx="80" cy="80" r="70" stroke-linecap="round" style="--value:${value}" />
                </svg>
            </div>
        </div>`;
    }
}

customElements.define('circle-progress', CircleProgress);