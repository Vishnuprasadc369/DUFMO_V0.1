import cv2
import socket
import time
import threading
import tkinter as tk
import keyboard

# Replace with your ESP32-CAM mDNS hostname
CAMERA_URL = 'http://esp32cam.local:81/stream'
ESP32_IP = 'Defmo32.local'  # Hos   `name for ESP32
ESP32_PORT = 80

control_running = True  # Global flag to manage the control loop

def stream_video():
    cap = cv2.VideoCapture(CAMERA_URL)
    cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)
    
    if not cap.isOpened():
        print("Error: Could not open video stream.")
        return

    while True:
        ret, frame = cap.read()
        if not ret:
            print("Failed to grab frame")
            break

        # Flip the image vertically
        frame = cv2.flip(frame, 0)

        cv2.imshow('ESP32-CAM Stream', frame)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cap.release()
    cv2.destroyAllWindows()

def send_message(sock, message):
    """Send a message to the ESP32 via the given socket and print the status."""
    try:
        sock.sendall(message.encode())
        time.sleep(0.1)
    except socket.error as e:
        print(f"Socket error while sending message: {e}")

def control_esp32(button_pressed, ir_label, touch_label):
    global control_running  # Access the global control flag
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    try:
        server_address = (ESP32_IP, ESP32_PORT)
        sock.connect(server_address)
        send_message(sock, ' \n')
        reset = 0

        while control_running:  # Use the global control flag
            if button_pressed.get() == 'up':
                send_message(sock, 'Forward,M1-100,M2-100\n')
             
            elif button_pressed.get() == 'down':
                send_message(sock, 'Backward,M1-100,M2-100\n')
                
            elif button_pressed.get() == 'left':
                send_message(sock, 'mood-0,left-1,right-0,hold-0\n')
                send_message(sock, 'Left,M1-100,M2-100\n')
                
            elif button_pressed.get() == 'right':
                send_message(sock, 'mood-0,left-0,right-1,hold-0\n')
                send_message(sock, 'Right,M1-100,M2-100\n')
                
            elif button_pressed.get() == 'stop':
                send_message(sock, 'Forward,M1-0,M2-0\n')
            button_pressed.set('stop')
            
            # Keyboard controls
            if keyboard.is_pressed('up'):
                send_message(sock, 'Forward,M1-100,M2-100\n')
            elif keyboard.is_pressed('down'):
                send_message(sock, 'Backward,M1-100,M2-100\n')
            elif keyboard.is_pressed('left'):
                send_message(sock, 'mood-0,left-1,right-0,hold-0\n')
                send_message(sock, 'Left,M1-100,M2-100\n')
            elif keyboard.is_pressed('right'):
                send_message(sock, 'mood-0,left-0,right-1,hold-0\n')
                send_message(sock, 'Right,M1-100,M2-100\n')
            elif keyboard.is_pressed(' '):
                send_message(sock, 'Forward,M1-0,M2-0\n')
            elif keyboard.is_pressed('q'):
                break  # Exit the loop if 'q' is pressed

            # Receive data from ESP32
            data = sock.recv(1024)
            if data:
                received_message = data.decode().strip()
                if "Touch-ON" in received_message:
                    touch_label.config(text="Touch: ON", bg="green")
                    send_message(sock, 'mood-6,left-0,right-0,hold-0\n')
                    send_message(sock, 'Sound-2\n')
                    send_message(sock, 'Right,M1-100,M2-100\n')
                    time.sleep(0.5)
                    send_message(sock, 'Left,M1-100,M2-100\n')
                    time.sleep(0.5)
                    send_message(sock, 'Right,M1-100,M2-100\n')
                    time.sleep(0.5)
                    send_message(sock, 'Left,M1-100,M2-100\n')
                    send_message(sock, 'Backward,M1-100,M2-100\n')
                    send_message(sock, 'Sound-2\n')
                    reset = 1
                elif "IR-OFF" in received_message:
                    ir_label.config(text="IR: OFF", bg="red")
                    send_message(sock, 'mood-3,left-0,right-0,hold-0\n')
                    send_message(sock, 'Backward,M1-100,M2-100\n')
                    reset = 1
                else:
                    if reset == 1:
                        send_message(sock, 'mood-1,left-0,right-0,hold-0\n')
                        time.sleep(2)
                        reset = 0
                    send_message(sock, 'mood-0,left-0,right-0,hold-0\n')
                    send_message(sock, 'Forward,M1-0,M2-0\n')

                    # Reset labels to indicate sensors are off
                    touch_label.config(text="Touch: OFF", bg="red")
                    ir_label.config(text="IR: OFF", bg="red")

    except Exception as e:
        print(f"Exception: {e}")
    finally:
        print('Closing connection')
        sock.close()

def create_gui():
    window = tk.Tk()
    window.title("ESP32 Motor Control")
    window.geometry("300x400")

    button_pressed = tk.StringVar()

    def on_button_press(direction):
        button_pressed.set(direction)
        control_thread = threading.Thread(target=control_esp32, args=(button_pressed, ir_label, touch_label))
        control_thread.start()

    # Create buttons with specific positions
    btn_forward = tk.Button(window, text="Forward", command=lambda: on_button_press('up'))
    btn_forward.place(x=100, y=50, width=100, height=50)

    btn_backward = tk.Button(window, text="Backward", command=lambda: on_button_press('down'))
    btn_backward.place(x=100, y=150, width=100, height=50)

    btn_left = tk.Button(window, text="Left", command=lambda: on_button_press('left'))
    btn_left.place(x=25, y=100, width=100, height=50)

    btn_right = tk.Button(window, text="Right", command=lambda: on_button_press('right'))
    btn_right.place(x=175, y=100, width=100, height=50)

    btn_stop = tk.Button(window, text="Stop", command=lambda: on_button_press('stop'))
    btn_stop.place(x=100, y=250, width=100, height=50)

    # Create labels for IR and touch sensor status
    ir_label = tk.Label(window, text="IR: ON", bg="red", fg="white")
    ir_label.place(x=100, y=310, width=100, height=30)

    touch_label = tk.Label(window, text="Touch: OFF", bg="red", fg="white")
    touch_label.place(x=100, y=350, width=100, height=30)

    def on_exit():
        global control_running
        control_running = False  # Stop the control loop
        window.destroy()  # Destroy the window

    window.protocol("WM_DELETE_WINDOW", on_exit)
    window.mainloop()

def main():
    # Start video streaming in a separate thread
    video_thread = threading.Thread(target=stream_video)
    video_thread.start()

    # Start the Tkinter GUI in the main thread
    create_gui()

    # After GUI exits, wait for video thread to complete
    video_thread.join()

if __name__ == "__main__":
    main()
