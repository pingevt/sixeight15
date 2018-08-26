var gulp = require('gulp');
var less = require('gulp-less');
var path = require('path');
var sourcemaps = require('gulp-sourcemaps');

var autoprefixer = require('gulp-autoprefixer');
var concat = require('gulp-concat');
var minifycss = require('gulp-minify-css');
var cleanCSS = require('gulp-clean-css');
var notify = require('gulp-notify');
var plumber = require('gulp-plumber');
var rename = require('gulp-rename');
var uglify = require('gulp-uglify');

gulp.task('less', function () {
  return gulp.src('./less/*.less')
    .pipe(plumber())
    .pipe(less())
    .pipe(autoprefixer({ browsers: ['last 3 versions'] }))
    .pipe(gulp.dest('./css'))
    .pipe(rename('style.min.css'))
    .pipe(minifycss())
    .pipe(gulp.dest('./css'))
    .pipe(notify({message: 'sixeight15: SCSS Compiled!'}));
});

gulp.task('watch', function ()
{
    gulp.watch('./less/**/*.less', ['less']);
});

gulp.task('default', ['watch']);
