mkdir out
mkdir tmp
curl -o tmp/1.html https://www.lyrics.com/serp.php?st=tinsel\&p=1
curl -o tmp/3.html https://www.lyrics.com/serp.php?st=tinsel\&p=2
grep -i "<em>tinsel" tmp/?.html > tmp/r1.txt
perl -ne '$_ =~ s/<[^>]+>//g; print' tmp/r1.txt  > tmp/r2.txt
perl -ne '$_ =~ s/^.+:\s*//g; print' tmp/r2.txt > out/final-lyrics.txt
say -v Samantha -o out/sam.aiff -f out/final-lyrics.txt 
say -v Karen -o out/karen.aiff -f out/final-lyrics.txt 
say -v Fiona -o out/fiona.aiff -f out/final-lyrics.txt 

 

