node('docker && imgtec') {
    def docker_image
    docker_image = docker.image "imgtec/creator-builder:latest" // TODO for now using the creator one
    docker_image.inside {
        stage('Prepare') {
            checkout scm
        }
        stage('Build') {
            sh 'make CROSS_COMPILE=/opt/toolchains/mips-img-linux-gnu/2016.05-03/bin/mips-img-linux-gnu- pistachio_marduk_defconfig'
            sh 'make CROSS_COMPILE=/opt/toolchains/mips-img-linux-gnu/2016.05-03/bin/mips-img-linux-gnu-'
        }
        stage('Upload') {
            archiveArtifacts 'u-boot-pistachio-nor.img'
        }
    }
}
