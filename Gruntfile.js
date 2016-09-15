module.exports = function(grunt) {

    // Project configuration.
    grunt.initConfig({
        pkg: grunt.file.readJSON('package.json'),

        'jshint': {
            'lint': {
                'options': {
                    'jshintrc': '.jshintrc',
                    'verbose': true,
                    'reporter': require('jshint-stylish')
                },
                'src': [
                    'index.js',
                    'lib/**/*.js',
                    'test/**/*.js'
                ]
            }
        },

        'mocha_istanbul': {
            'coverage': {
                'src': 'test',
                'options': {
                    'print': 'detail',
                    'reporter': 'spec'
                }
            }
        },

        'coveralls': {
            'options': {
                // LCOV coverage file relevant to every target
                'src': 'coverage/lcov.info',

                // When true, grunt-coveralls will only print a warning rather than
                // an error, to prevent CI builds from failing unnecessarily (e.g. if
                // coveralls.io is down). Optional, defaults to false.
                'force': true
            },
            'px2-local-handler': 'coverage/lcov.info'
        }

    });

    grunt.loadNpmTasks('grunt-contrib-jshint');
    grunt.loadNpmTasks('grunt-mocha-istanbul');
    grunt.loadNpmTasks('grunt-coveralls');
    grunt.registerTask('test', ['jshint', 'mocha_istanbul', 'coveralls']);

};