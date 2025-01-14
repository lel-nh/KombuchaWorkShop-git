import serial
import time
import matplotlib.pyplot as plt

# Configuration du port série (remplacez 'COM3' par le port utilisé par votre Arduino)
try:
    arduino = serial.Serial('/dev/cu.usbserial-14320', 115200, timeout=1)
    time.sleep(2)
    print("Connexion série établie avec Arduino.")
except serial.SerialException as e:
    print(f"Erreur de connexion série : {e}")
    exit()

# Listes pour stocker les données
signal_values = []
noise_values = []
snr_values = []

# Tracé en temps réel
plt.ion()
fig, ax = plt.subplots()
line_signal, = ax.plot([], [], label="Signal", color="blue")
line_noise, = ax.plot([], [], label="Bruit", color="orange")
line_snr, = ax.plot([], [], label="SNR (dB)", color="green")
ax.set_title("Signal, Bruit et SNR")
ax.set_xlabel("Échantillons")
ax.set_ylabel("Valeurs")
ax.legend()

try:
    while True:
        if arduino.in_waiting > 0:  # Vérifie si des données sont disponibles
            data = arduino.readline().decode('utf-8').strip()
            if "Signal" in data:  # Parse les données série
                try:
                    parts = data.split(", ")
                    signal = int(parts[0].split(": ")[1])
                    noise = int(parts[1].split(": ")[1])
                    snr = float(parts[2].split(": ")[1])

                    # Ajouter les données aux listes
                    signal_values.append(signal)
                    noise_values.append(noise)
                    snr_values.append(snr)

                    # Limiter le nombre d'échantillons affichés
                    if len(signal_values) > 100:
                        signal_values.pop(0)
                        noise_values.pop(0)
                        snr_values.pop(0)

                    # Mettre à jour le graphe
                    line_signal.set_ydata(signal_values)
                    line_signal.set_xdata(range(len(signal_values)))
                    line_noise.set_ydata(noise_values)
                    line_noise.set_xdata(range(len(noise_values)))
                    line_snr.set_ydata(snr_values)
                    line_snr.set_xdata(range(len(snr_values)))

                    ax.relim()
                    ax.autoscale_view()
                    plt.pause(0.01)
                except ValueError:
                    print("Erreur lors du parsing des données :", data)

except KeyboardInterrupt:
    print("Arrêt par l'utilisateur.")
finally:
    arduino.close()
    print("Connexion série fermée.")
    plt.ioff()
    plt.show()
