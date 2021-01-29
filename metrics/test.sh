echo 'Testing pred.csv (answer should be 0.69291157440690143):'
./f1 tests/ans.csv tests/pred.csv tests/t2_pub.csv
echo 'Tetsing .csv with ",": '
./f1 tests/ans.csv tests/pred_comma.csv tests/t2_pub.csv
echo 'Testing .csv with ";": '
./f1 tests/ans.csv tests/pred_semi.csv tests/t2_pub.csv
echo 'Testing execution time:'
time -p ./f1 tests/ans.csv tests/pred_comma.csv tests/t2_pub.csv
