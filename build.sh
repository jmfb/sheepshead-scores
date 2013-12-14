clear

echo Building ViewCompiler...
g++ -std=c++0x ./ViewCompiler/*.cpp -o ./ViewCompiler/ViewCompiler 3>&1 1>&2 2>&3 3>&- | head
echo Compiling views...
ls *.view.html | ./ViewCompiler/ViewCompiler | head

echo Building CommandCompiler...
g++ -std=c++0x ./CommandCompiler/*.cpp -o ./CommandCompiler/CommandCompiler 3>&1 1>&2 2>&3 3>&- | head
echo Compiling commands...
ls *.command.sql | ./CommandCompiler/CommandCompiler | head

echo Building CGI...
g++ -std=c++0x *.cpp -lpqxx -lpq -o /var/www/sheepshead.cgi 3>&1 1>&2 2>&3 3>&- | head

#TODO: Minified Angular controller was not working.
#echo Minifying Javascript...
#java -jar /usr/share/yui-compressor/yui-compressor.jar -o '.js$:.min.js' *.js

echo Copying source files...
rm -f /var/www/*.css
rm -f /var/www/*.js
cp *.ico /var/www/
#mv *.min.js /var/www/
cp *.js /var/www/

