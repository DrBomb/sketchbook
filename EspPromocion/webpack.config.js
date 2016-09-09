module.exports = {
    entry:"./assets/entry.js",
    output:{
        path:"./data/",
        filename:"bundle.js"
    },
    module:{
        loaders: [
            { test: /\.jpg$/, loader:"base64-image"},
            {
                test: /\.js$/,
                exclude: /node_modules/,
                loader: 'babel',
                query: {
                    presets: ['es2015','react']
                }
            }
        ]
    }
}
