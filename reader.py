import numpy as np
import cv2
import subprocess

def process_image(image, idx):
    header = f'{int(len(image.shape) == 2)} {image.shape[0]} {image.shape[1]} '.encode()
    bytes = image.tobytes()

    result = subprocess.run(['./gradient_finder'], input=header + bytes, stdout=subprocess.PIPE)
    result = result.stdout.decode('utf-8')
    ans = list(map(int, result.split(' ')))
    print(ans)

    cv2.rectangle(image, (ans[0], ans[2]), (ans[1], ans[3]), color=(0, 255, 0), thickness=3)
    cv2.imwrite(f'images/{idx}.jpg', image)



h = 1000
w = 1000
idx = 0
for x, y in zip([100, 250], [60, 300]):
    for width, height in zip([10, 144], [111, 65]):
        image = np.random.randint(low=0, high=255, size=(h, w, 3), dtype=np.uint8)
        idx += 1
        for i in range(x, x + width):
            for j in range(y, y + height):
                c = i - x + j - y
                image[j][i][0] = c
                image[j][i][1] = c
                image[j][i][2] = c
        process_image(image, idx)

        image = np.random.randint(low=0, high=255, size=(h, w, 3), dtype=np.uint8)
        idx += 1
        for i in range(x, x + width):
            for j in range(y, y + height):
                c = i - x
                image[j][i][0] = c
                image[j][i][1] = c
                image[j][i][2] = c
        process_image(image, idx)

        image = np.random.randint(low=0, high=255, size=(h, w, 3), dtype=np.uint8)
        idx += 1
        for i in range(x, x + width):
            for j in range(y, y + height):
                c = j - y
                image[j][i][0] = c
                image[j][i][1] = c
                image[j][i][2] = c
        process_image(image, idx)