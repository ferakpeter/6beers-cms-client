const path = require('path');
const outputDir = path.join(__dirname, "public/");

const isProd = process.env.NODE_ENV === 'production';

module.exports = {
  entry: './src/index.js',
  mode: isProd ? 'production' : 'development',
  output: {
    path: outputDir,
    publicPath: outputDir,
    filename: 'main.js',
  },
};
