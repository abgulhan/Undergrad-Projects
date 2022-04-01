import sys
import csv
import numpy as np
import pandas as pd
from sklearn.feature_selection import RFECV
from sklearn.decomposition import PCA
from sklearn.metrics import classification_report, confusion_matrix
from sklearn.svm import SVR
from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import train_test_split 
from sklearn.preprocessing import StandardScaler


def loadData(filename):

    dataframe = pd.read_csv(filename)
    return dataframe



def preprocessing(dataframe, dataframe_test = None, all = False, test = False): #all = true means use all of data for training
    array = dataframe.values
    
    X = array[:,0:len(array[0])-1]
    Y = array[:,len(array[0])-1]

    #standardize data
    sc = StandardScaler()
    X = sc.fit_transform(X)

    #reduce unnecessary features
    estimator = SVR(kernel='linear', gamma='scale') 
    selector = RFECV(estimator, step=5, cv=5, min_features_to_select = 12) #cv=5 -> 5 fold cross validation, setp=1 -> remove 5 feature every iteration
    fit = selector.fit(X, Y)
    
    selected = fit.support_
    #print(selected)
    for i in range(len(selected)):
        if(selected[i] == True):
            selected[i] = 1
        else:
            selected[i] = 0
    #remove unneccesary features
    X = X[:, selected]

    #use pca to reduce features to 12
    pca = PCA(svd_solver = 'arpack', n_components = 12) #get 12 features
    X = pca.fit_transform(X)


    if(test): #don't split data into test and train data
        array = dataframe_test.values
        #print(array.shape)
        X = array[:,0:len(array[0])]
        X = X[:, selected]
        X = sc.fit_transform(X)
        pca = PCA(svd_solver = 'arpack', n_components = 12) #get 12 features
        X = pca.fit_transform(X)
        return X

    if(all):
        return X, Y

    else: #use 0.2 of data as testing set and 0.8 as training set
        #dividing data into train and test  (chooses randomly)
        X_train, X_test, Y_train, Y_test = train_test_split(X, Y, test_size = 0.2) 
        return X_train, X_test, Y_train, Y_test


def trainModel(X,Y):
    clf = RandomForestClassifier(criterion='gini', max_depth=None, n_estimators=15, random_state = 0) #can change n_estimators
    clf.fit(X, Y) 
    return clf
    
def Predict(X, Y, clf):
    predicted_values = clf.predict(X)
    #print(confusion_matrix(Y, predicted_values))
    print(classification_report(Y, predicted_values))


def writeOutput(X, neigh, filename):
    predicted_values = neigh.predict(X)
    with open(filename, mode='w') as filename:
        writer = csv.writer(filename)

        writer.writerow(['ID','Predicted'])
        for i in range(len(predicted_values)):
            line1 = str(i+1)
            line2 = str(int(predicted_values[i]))
            writer.writerow([line1, line2])

def main(): 

    is_sub = False  #set true if you want to train with entire input data, and make a submission file
                    #set as false if you want to train with 80% of data and check with 20%.  Makes no submission file

    if(len(sys.argv) < 2):
        print("usage is python3 ./<filename>.py -s for predicting test file")
        print("usage is python3 ./<filename>.py -t for viewing test accuracy (train and test selected randomly so each run has different results)")
        print("input file names:  'train.csv' and 'test.csv'")
        print("output is made to 'submission.csv'")
        exit()
        

    if(sys.argv[1] == "-s"):
        is_sub = True
    elif(sys.argv[1] == "-t"):
        is_sub = False
    else:
        print("invalid parameters. Should be '-t' or '-s'")
        exit()
        
    dataframe = loadData("./train.csv")
    dataframe_test = loadData("./test.csv")




    if(is_sub):#train with entire data
        X_train, Y_train = preprocessing(dataframe, all = True)
        X_test = preprocessing(dataframe, dataframe_test, test = True)
        
        clf = trainModel(X_train, Y_train) # clf is our model
        
        writeOutput(X_test, clf, "submission.csv")
        
    else:#train with 80% of data and check accuracy with 20%
        X_train, X_test, Y_train, Y_test = preprocessing(dataframe)
        clf = trainModel(X_train, Y_train) #clf is our model
        Predict(X_test, Y_test, clf)


if __name__ == "__main__":
    main()
