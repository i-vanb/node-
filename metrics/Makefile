CC=g++
FLAGS=-std=c++11 -c -O3

all: rmsle f1 accuracy log_loss hit hit_2 wrmse roc_auc balanced_accuracy rmape mae rmse mapk eer average_auc average_auc6

log_loss: log_loss.o utils.o
	$(CC) log_loss.o utils.o -o log_loss

log_loss.o: log_loss.cpp
	$(CC) $(FLAGS) log_loss.cpp

mapk: mapk.o
	$(CC) mapk.o -o mapk

mapk.o: mapk.cpp
	$(CC) $(FLAGS) mapk.cpp

hit: hit.o utils.o
	$(CC) hit.o utils.o -o hit

hit.o: hit.cpp
	$(CC) $(FLAGS) hit.cpp

hit_2: hit_2.o utils.o
	$(CC) hit_2.o utils.o -o hit_2

hit_2.o: hit_2.cpp
	$(CC) $(FLAGS) hit_2.cpp

rmsle: rmsle.o utils.o
	$(CC) rmsle.o utils.o -o rmsle

rmsle.o: rmsle.cpp
	$(CC) $(FLAGS) rmsle.cpp


mae: mae.o utils.o
	$(CC) mae.o utils.o -o mae

mae.o: mae.cpp
	$(CC) $(FLAGS) mae.cpp

rmape: rmape.o utils.o
	$(CC) rmape.o utils.o -o mape

rmape.o: rmape.cpp
	$(CC) $(FLAGS) rmape.cpp

eer: eer.o utils.o
	$(CC) eer.o utils.o -o eer

eer.o: eer.cpp
	$(CC) $(FLAGS) eer.cpp

wrmse: wrmse.o utils.o
	$(CC) wrmse.o utils.o -o wrmse

wrmse.o: wrmse.cpp
	$(CC) $(FLAGS) wrmse.cpp

rmse: rmse.o utils.o
	$(CC) rmse.o utils.o -o rmse

rmse.o: rmse.cpp
	$(CC) $(FLAGS) rmse.cpp

utils.o: utils.cpp
	$(CC) $(FLAGS) utils.cpp	

f1: f1_score.o utils.o
	$(CC) f1_score.o utils.o -o f1

f1_score.o: f1_score.cpp
	$(CC) $(FLAGS) f1_score.cpp

accuracy: accuracy.o utils.o
	$(CC) accuracy.o utils.o -o accuracy

accuracy.o: accuracy.cpp
	$(CC) $(FLAGS) accuracy.cpp

balanced_accuracy: balanced_accuracy.o utils.o
	$(CC) balanced_accuracy.o utils.o -o balanced_accuracy

balanced_accuracy.o: balanced_accuracy.cpp
	$(CC) $(FLAGS) balanced_accuracy.cpp

average_auc: average_auc.o utils.o
	$(CC) average_auc.o utils.o -o average_auc

average_auc.o: average_auc.cpp
	$(CC) $(FLAGS) average_auc.cpp

average_auc6: average_auc6.o utils.o
	$(CC) average_auc6.o utils.o -o average_auc6

average_auc6.o: average_auc6.cpp
	$(CC) $(FLAGS) average_auc6.cpp

roc_auc: roc_auc.o utils.o
	$(CC) roc_auc.o utils.o -o auc

roc_auc.o: roc_auc.cpp
	$(CC) $(FLAGS) roc_auc.cpp

clean:
	rm -rf *.o rmsle

