#ifndef DATAREADER_H
#define DATAREADER_H

#include <QString>
#include <QFile>
#include <QTextStream>

#include <basictypes.h>
#include <physycobject.h>.h>



class DataReader
{
public:
    DataReader();
    static   int readFile(const  QString& fileName, PhObject& object)
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return -1;

        QTextStream in(&file);
        return process_file(in, object);
    }

private:
    static int process_file(QTextStream& in, PhObject& object)
    {
        object.external_constrains.clear();
        object.meshs.clear();

        int object_count = 0;
        in >> object_count;
        object.meshs.resize(object_count);

        for (int i =0; i < object_count; i++)
        {
            auto& mesh = object.meshs[i];

            QString strSubobject;
            in >> strSubobject;
            if (strSubobject != QString("subobject"))
                return -2;


            int points_count = 0;
            in >> points_count;
            mesh.points.resize(points_count);

            for (int j = 0; j < points_count; ++j)
            {
                double x = 0.0;
                double y = 0.0;
                in >> x >> y;
                mesh.points[j] = {x,y};
            }

            int constrain_count = 0;
            in >> constrain_count;
            mesh.constrains.resize(constrain_count);
            for (int j = 0; j < constrain_count; ++j)
            {
                int a = 0.0;
                int b = 0.0;
                in >> a >> b;
                // size of constrains doesnot readed, it's scalculated
                mesh.constrains[j] = {a,b};
            }
        }

        QString constrain_str;
        in >> constrain_str;
        if ( constrain_str != "external_constrain")
            return -3;
        int ext_constrain_count = 0;
        in >> ext_constrain_count;
        object.external_constrains.resize(ext_constrain_count);
        for (int i = 0; i < ext_constrain_count; ++i)
        {
            int meshA = 0;
            int meshB = 0;
            int pointA = 0;
            int pointB = 0;
            in >> meshA >> pointA >> meshB>> pointB;
            object.external_constrains[i] = {meshA, pointA, meshB, pointB};
        }
        return 0;
    }
};

#endif // DATAREADER_H
