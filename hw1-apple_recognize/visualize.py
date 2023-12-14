import cv2


def mouse_callback(event, x, y, flags, param):
    if event == cv2.EVENT_LBUTTONDOWN:
        if param == 0:
            h_value = h[y, x]  # 提取H通道值
            print(f"Hue at ({x}, {y}): {h_value}")
        if param == 1:
            s_value = s[y, x]  # 提取S通道值
            print(f"Saturation at ({x}, {y}): {s_value}")
        if param == 2:
            v_value = v[y, x]  # 提取V通道值
            print(f"Value at ({x}, {y}): {v_value}")


# 读取图像并转换为HSV颜色空间
image = cv2.imread("apple.png")

# 这里好像不能写!=
assert image is not None, "Failed to load image."

hsv_image = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)

# 存储hsv三通道的值
h, s, v = cv2.split(hsv_image)
cv2.imshow("Image", image)


# 设置鼠标回调函数
a = 0
cv2.imshow("Hue", h)
if a == 0:
    cv2.imshow("Hue", h)
    cv2.setMouseCallback("Hue", mouse_callback, a)
if a == 1:
    cv2.imshow("Saturation", s)
    cv2.setMouseCallback("Saturation", mouse_callback, a)
if a == 2:
    cv2.imshow("Value", v)
    cv2.setMouseCallback("Value", mouse_callback, a)


while True:
    key = cv2.waitKey(1) & 0xFF
    if key == 27:  # 按下ESC键退出循环
        break

cv2.destroyAllWindows()
