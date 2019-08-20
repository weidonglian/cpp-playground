pipeline {
    agent { dockerfile true }
    environment {
        CI = 'true'
    }
    stages {
        stage('Build') {
            steps {
                sh 'mkdir -p build && cd build && cmake .. && make'
            }
        }
        stage('Test') {
            steps {
                sh 'cd build && ctest --verbose'
            }
        }
        stage('Deliver') {
            steps {
                sh 'echo "Deploying."'
            }
        }
    }
}
