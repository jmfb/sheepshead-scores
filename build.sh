clear

echo Building ViewCompiler...
g++ -std=c++0x ./ViewCompiler/*.cpp -o ./ViewCompiler/ViewCompiler 3>&1 1>&2 2>&3 3>&- | head
echo Compiling views...
ls ./Views/*.view.html | ./ViewCompiler/ViewCompiler | head

echo Building CommandCompiler...
g++ -std=c++0x ./CommandCompiler/*.cpp -o ./CommandCompiler/CommandCompiler 3>&1 1>&2 2>&3 3>&- | head
echo Compiling commands...
ls ./Commands/*.command.sql | ./CommandCompiler/CommandCompiler | head

echo Building CGI...
VAR_PWD=`pwd`
g++ -std=c++0x -I$VAR_PWD -I./Models/ -I./Generated/ *.cpp ./Models/*.cpp ./Generated/*.cpp -lpqxx -lpq -o /var/www/sheepshead.cgi 3>&1 1>&2 2>&3 3>&- | head

echo Copying source files...
rm -f /var/www/*.css
rm -f /var/www/*.js
cp ./Images/*.ico /var/www/
cp ./Scripts/*.js /var/www/

