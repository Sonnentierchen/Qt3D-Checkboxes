/****************************************************************************
**
** Copyright (C) 2014 Klaralvdalens Datakonsult AB (KDAB).
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "scenemodifier.h"

#include <QtCore/QDebug>
#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QConeMesh>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QPhongMaterial>

SceneModifier::SceneModifier(Qt3DCore::QEntity *rootEntity)
    : m_rootEntity(rootEntity)
{
    entites.append(m_rootEntity);
}

SceneModifier::~SceneModifier() {
}

void SceneModifier::addRandomEntity(bool enabled) {
    Qt3DCore::QEntity *newObject = new Qt3DCore::QEntity(entites.last());
    Qt3DRender::QGeometryRenderer *newMesh;
    int current = entites.length();
    switch(current % 3) {
        case 0: {
            Qt3DExtras::QSphereMesh *mesh = new Qt3DExtras::QSphereMesh;
            mesh->setRadius(1.0);
            mesh->setRings(100);
            mesh->setSlices(100);
            newMesh = mesh;
            qDebug() << "Adding sphere.";
            break;
        }
        case 1: {
            newMesh = new Qt3DExtras::QCuboidMesh;
            qDebug() << "Adding cuboid.";
            break;
        }
        case 2: {
            Qt3DExtras::QTorusMesh *mesh = new Qt3DExtras::QTorusMesh;
            mesh->setRadius(1.0);
            mesh->setMinorRadius(0.3);
            mesh->setRings(100);
            mesh->setSlices(100);
            newMesh = mesh;
            qDebug() << "Adding torus.";
            break;
        }
    }
    newObject->addComponent(newMesh);
    Qt3DExtras::QPhongMaterial *phongMaterial = new Qt3DExtras::QPhongMaterial;
    newObject->addComponent(phongMaterial);
    Qt3DCore::QTransform *transform = new Qt3DCore::QTransform;

    // distribute in grid
    transform->setTranslation(QVector3D(current - 2,
                                        0,
                                        0));
    qDebug() << transform->translation();
    newObject->addComponent(transform);
    newObject->setEnabled(enabled);
    entites.append(newObject);
}

void SceneModifier::enableEntity(bool enabled, int index) {
    entites[index + 1]->setEnabled(enabled);
}
