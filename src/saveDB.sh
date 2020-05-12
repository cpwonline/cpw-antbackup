USER="jfrc26"
PASSWORD="-2160JfRc*"
DATABASE="jfrc26"
FINAL_OUTPUT=backups/`date +%Y%m%d`_$DATABASE.sql

mysqldump --user=$USER --password=$PASSWORD $DATABASE > $FINAL_OUTPUT

gzip $FINAL_OUTPUT