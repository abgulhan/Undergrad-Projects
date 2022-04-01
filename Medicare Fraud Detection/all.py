import sys
import csv
import numpy as np
import pandas as pd
from sklearn.feature_selection import RFECV
from sklearn.metrics import classification_report, confusion_matrix, roc_auc_score
from sklearn.svm import SVR
from sklearn.model_selection import train_test_split 
from sklearn.preprocessing import StandardScaler
from imblearn.over_sampling import SMOTE, ADASYN, RandomOverSampler
from imblearn.combine import SMOTETomek
from imblearn.under_sampling import RandomUnderSampler
from sklearn.linear_model import LogisticRegression
from sklearn import tree
from sklearn.ensemble import RandomForestClassifier



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


    X_train, X_test, Y_train, Y_test = train_test_split(X, Y, test_size = 0.2) 
    return X_train, X_test, Y_train, Y_test
        


def trainModel(X,Y):
    sampler = SMOTE(sampling_strategy = 1/1, random_state=42)
    #sampler = SMOTETomek(sampling_strategy = 1/9, random_state=42)
    #sampler = ADASYN(sampling_strategy = 1/9, random_state=42)
    #sampler = RandomUnderSampler(sampling_strategy = 1/1, random_state=42)
    #sampler = RandomOverSampler(sampling_strategy = 1/1, random_state=42)
    X, Y = sampler.fit_resample(X, Y)
    clf = RandomForestClassifier(criterion='gini', max_depth=None, n_estimators=15, random_state = 0) #can change n_estimators
    #clf = tree.DecisionTreeClassifier()
    #clf = LogisticRegression(random_state = 0)
    clf.fit(X, Y) 
    return clf
    
def Predict(X, Y, clf):
    predicted_values = clf.predict(X)
    #print(confusion_matrix(Y, predicted_values))
    print(classification_report(Y, predicted_values))
    print("roc_auc_score: ", roc_auc_score(Y, predicted_values))


def main(): 

        
    #dataframe = loadData("kaggle.csv")
    dataframe = loadData("combine.csv")
    ### Lets check missing value percentage in full datasets


    #train with 80% of data and check accuracy with 20%
    X_train, X_test, Y_train, Y_test = preprocessing(dataframe)
    clf = trainModel(X_train, Y_train) #clf is our model
    Predict(X_test, Y_test, clf)
    print("dataset: kaggle.csv")
    print("method: RandomForestClassifier")
    print("sampler: SMOTETomek")
    print("ratio: 90:10")
    

if __name__ == "__main__":
    main()
