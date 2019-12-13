#curl -o 1.html https://www.lyrics.com/serp.php?st=tinsel\&p=1
#curl -o 3.html https://www.lyrics.com/serp.php?st=tinsel\&p=2
grep -i "<em>tinsel" ?.html > r1.txt
perl -ne '$_ =~ s/<[^>]+>//g; print' r1.txt  > r2.txt
perl -ne '$_ =~ s/^.+:\s*//g; print' r2.txt

