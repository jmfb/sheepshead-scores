clear
g++ -std=c++0x *.cpp -lpqxx -lpq -o /var/www/sheepshead.cgi 3>&1 1>&2 2>&3 3>&- | head
cp *.ico /var/www/
cp *.js /var/www/
cp *.css /var/www/

