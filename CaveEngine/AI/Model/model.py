from tensorflow.keras import Input, Sequential
from tensorflow.keras.layers import Dense

x = [[0, 0], [0, 1], [1, 0], [1, 1]]
y = [[0], [1], [1], [0]]

model = Sequential([
    Input(shape=(2,), name='input', dtype='int32'),
    Dense(16, activation='relu'),
    Dense(1, activation='sigmoid', name='output')
])
model.summary()

model.compile(optimizer='adam', loss='mse', metrics=['acc'])

history = model.fit(x, y, epochs=500, verbose=2)

model.save('CaveEngine/AI/Data/SavedModel')  # save as tf saved model

model.predict(x)  # test