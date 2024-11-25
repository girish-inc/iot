            import RPi.GPIO as GPIO
            from flask import Flask, render_template, request

            app = Flask(__name__)

            # GPIO Setup
            GPIO.setmode(GPIO.BCM)
            GPIO.setwarnings(False)

            # LED Pins
            ledRed = 13
            ledYellow = 19
            ledGreen = 26

            # Initial LED Status
            ledRedSts = 0
            ledYellowSts = 0
            ledGreenSts = 0

            # GPIO Pin Configuration
            GPIO.setup(ledRed, GPIO.OUT)
            GPIO.setup(ledYellow, GPIO.OUT)
            GPIO.setup(ledGreen, GPIO.OUT)

            # Initial LED State
            GPIO.output(ledRed, GPIO.LOW)
            GPIO.output(ledYellow, GPIO.LOW)
            GPIO.output(ledGreen, GPIO.LOW)

            @app.route('/')
            def index():
                # Get current LED status
                ledRedSts = GPIO.input(ledRed)
                ledYellowSts = GPIO.input(ledYellow)
                ledGreenSts = GPIO.input(ledGreen)

                # Prepare template data
                templateData = {
                    'ledRed': ledRedSts,
                    'ledYellow': ledYellowSts,
                    'ledGreen': ledGreenSts
                }

                return render_template('index.html', **templateData)

            @app.route('/<deviceName>/<action>')
            def do(deviceName, action):
                # Select the correct LED based on device name
                if deviceName == "ledRed":
                    actuator = ledRed
                elif deviceName == "ledYellow":
                    actuator = ledYellow
                elif deviceName == "ledGreen":
                    actuator = ledGreen
                else:
                    return "Invalid device"

                # Perform the action
                if action == "on":
                    GPIO.output(actuator, GPIO.HIGH)
                elif action == "off":
                    GPIO.output(actuator, GPIO.LOW)

                # Get updated LED status
                ledRedSts = GPIO.input(ledRed)
                ledYellowSts = GPIO.input(ledYellow)
                ledGreenSts = GPIO.input(ledGreen)

                # Prepare template data
                templateData = {
                    'ledRed': ledRedSts,
                    'ledYellow': ledYellowSts,
                    'ledGreen': ledGreenSts
                }

                return render_template('index.html', **templateData)

            if __name__ == "__main__":
                app.run(host='0.0.0.0', debug=True)