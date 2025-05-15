import numpy as np
import matplotlib.pyplot as plt
from sklearn.neighbors import KNeighborsClassifier

# 닥스훈트 데이터 생성
dachshund_length = np.random.randint(70, 90, size=200)
dachshund_height = np.random.randint(20, 40, size=200)

# 사모예드 데이터 생성
samoyed_length = np.random.randint(70, 90, size=200)
samoyed_height = np.random.randint(50, 70, size=200)

# 평균값 계산
dachshund_length_mean = np.mean(dachshund_length)
dachshund_height_mean = np.mean(dachshund_height)

samoyed_length_mean = np.mean(samoyed_length)
samoyed_height_mean = np.mean(samoyed_height)

# 정규분포를 이용한 데이터 생성
new_dachshund_length_data = np.random.normal(dachshund_length_mean, 10.0, 200)
new_dachshund_height_data = np.random.normal(dachshund_height_mean, 10.0, 200)

new_samoyed_length_data = np.random.normal(samoyed_length_mean, 10.0, 200)
new_samoyed_height_data = np.random.normal(samoyed_height_mean, 10.0, 200)

# 데이터 합치기
new_dachshund_data = np.column_stack((new_dachshund_length_data, new_dachshund_height_data))
new_samoyed_data = np.column_stack((new_samoyed_length_data, new_samoyed_height_data))

# 라벨링
dachshund_label = np.zeros(len(new_dachshund_data))
samoyed_label = np.ones(len(new_samoyed_data))

# 데이터 병합
X = np.concatenate((new_dachshund_data, new_samoyed_data), axis=0)
y = np.concatenate((dachshund_label, samoyed_label), axis=0).astype(int)

# KNN 모델 학습
k = 3
knn = KNeighborsClassifier(n_neighbors=k)
knn.fit(X, y)

# 훈련 정확도 계산 추가
y_train_pred = knn.predict(X)
train_accuracy = np.mean(y_train_pred == y)
print(f"훈련 정확도: {train_accuracy:.2f}")

# 새로운 개 5마리 데이터 생성 및 예측
dog_length = np.random.randint(1, 100, size=5)
dog_height = np.random.randint(1, 70, size=5)
new_dog_data = np.column_stack((dog_length, dog_height))

# 품종 예측
y_predict = knn.predict(new_dog_data)

dog_classes = {0: "닥스훈트", 1: "사모예드"}
print(f"예측 결과: {', '.join([dog_classes[y] for y in y_predict])}")

# 데이터 시각화
plt.figure(figsize=(8, 6))
plt.scatter(new_dachshund_data[:, 0], new_dachshund_data[:, 1], color='red', label='닥스훈트')
plt.scatter(new_samoyed_data[:, 0], new_samoyed_data[:, 1], color='blue', label='사모예드')
plt.scatter(new_dog_data[:, 0], new_dog_data[:, 1], color='green', marker='*', s=200, label='예측 대상')
plt.xlabel('길이 (cm)')
plt.ylabel('높이 (cm)')
plt.legend()
plt.title('닥스훈트 vs 사모예드 데이터 분포표')
plt.show()
