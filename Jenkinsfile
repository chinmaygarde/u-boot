node('docker && imgtec') {
    def docker_image
    docker_image = docker.image "imgtec/creator-builder:latest" // TODO for now using the creator one
    docker_image.inside {
        stage('Prepare') {
            checkout([$class: 'GitSCM',
                userRemoteConfigs: scm.userRemoteConfigs,
                branches: scm.branches,
                doGenerateSubmoduleConfigurations: scm.doGenerateSubmoduleConfigurations,
                submoduleCfg: scm.submoduleCfg,
                browser: scm.browser,
                gitTool: scm.gitTool,
                extensions: scm.extensions + [
                    [$class: 'CleanCheckout'],
                    [$class: 'PruneStaleBranch'],
                ],
            ])
        }
        stage('Build') {
            sh 'make CROSS_COMPILE=/opt/toolchains/mips-img-linux-gnu/2016.05-03/bin/mips-img-linux-gnu- pistachio_marduk_defconfig'
            sh 'make CROSS_COMPILE=/opt/toolchains/mips-img-linux-gnu/2016.05-03/bin/mips-img-linux-gnu-'
        }
        stage('Upload') {
            archiveArtifacts 'u-boot-pistachio*.img'
        }
    }
}
