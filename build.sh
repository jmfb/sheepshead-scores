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

echo Copying source files...
cp *.ico /var/www/
cp *.js /var/www/
cp *.css /var/www/

