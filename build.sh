clear
g++ -std=c++0x *.cpp -o /var/www/sheepshead.cgi 3>&1 1>&2 2>&3 3>&- | head
cp favicon.ico /var/www/favicon.ico
cp *.js /var/www/
cp *.css /var/www/

