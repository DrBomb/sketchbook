import React from 'react';
import ReactDOM from 'react-dom';
var images = require('./images.js');

class Foto extends React.Component {
    render(){
        return(<img src={this.props.data} />);
    }
}

class Fotos extends React.Component {
    render(){
        return (
                <div className="fotos">
            {this.props.data.map(function(entry,i){
                 return(<Foto data={entry} />);
            })}
            </div>
            );
        }
}

ReactDOM.render(<Fotos data={images} />, document.getElementById("container"));
