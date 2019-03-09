#include "CodeViewModel.h"

CodeViewModel::CodeViewModel() {
}

QString CodeViewModel::name() const {
    return m_name;
}

QString CodeViewModel::description() const {
    return m_description;
}

QString CodeViewModel::code() const {
    return m_code;
}

QString CodeViewModel::barcodeType() const {
    return m_type;
}

void CodeViewModel::update(CodeViewModel *other) {
    m_name = other->name();
    m_description = other->description();
    m_code = other->code();
    m_type = other->barcodeType();

    emit nameChanged(m_name);
    emit descriptionChanged(m_description);
    emit codeChanged(m_code);
    emit barcodeTypeChanged(m_code);
}

CodeViewModel *CodeViewModel::clone() {
    CodeViewModel* clone = new CodeViewModel();
    clone->setName(m_name);
    clone->setDescription(m_description);
    clone->setCode(m_code);
    clone->setBarcodeType(m_type);

    return clone;
}

void CodeViewModel::setName(QString arg) {
    if (m_name != arg) {
        m_name = arg;
        emit nameChanged(arg);
    }
}

void CodeViewModel::setDescription(QString arg) {
    if (m_description != arg) {
        m_description = arg;
        emit descriptionChanged(arg);
    }
}

void CodeViewModel::setCode(QString arg) {
    if (m_code != arg) {
        m_code = arg;
        emit codeChanged(arg);
    }
}

void CodeViewModel::setBarcodeType(QString arg) {
    if (m_type != arg) {
        m_type = arg;
        emit barcodeTypeChanged(arg);
    }
}

QString CodeViewModel::generateCode(QString code, QString barcodeType) {
    QString encoded;

    if ( barcodeType == "0" ) {  // code 128
        encoded.prepend(QChar(codeToChar(CODE128_B_START)));  // Start set with B Code 104
        encoded.append(code);
        encoded.append(QChar(calculateCheckCharacter(code)));
        encoded.append(QChar(codeToChar(CODE128_STOP)));  // End set with Stop Code 106
    }

    if ( barcodeType == "1" ) { // EAN 8
        /* It resembles EAN 13 very much.
           It has 7 digits and a checksum computed exactly in the same way as for code EAN13.
           The delimiters left (We shall use ASCII 58), middle and right are the same ones.
           The first 4 digits are build with table A and the last 4 ones with the table C.'
           Parameters : a 7 digits length string
           Return : * a string which give the bar code when it is dispayed with EAN13.TTF font
        */
        int i;
        QString barcode;
        if (code.count() == 7) {
            int checksum = 0;
            // no 8th (checksum) number entered
            for ( i = 6; i >= 0; i-=2 ) {
                checksum = checksum + code.mid(i, 1).toInt();
            }
            checksum = checksum * 3;
            for ( i = 5; i >= 0; i-=2 ) {
                checksum = checksum + code.mid(i, 1).toInt();
            }
            code = code.append(QString::number((10 - checksum % 10) % 10));
        }
        barcode = ":";  // Add start mark
        for ( i = 0; i < 4; i+=1 ) {
            barcode = barcode + static_cast<char>(65 + code.mid(i, 1).toInt());
        }
        barcode = barcode + "*";  // Add middle separator
        for ( i = 4; i < 8; i+=1 ) {
            barcode = barcode + static_cast<char>(97 + code.mid(i, 1).toInt());
        }
        barcode = barcode + "+";  // Add end mark
        // QTextStream(stdout) << "barcode = " << barcode;
        encoded = barcode;
    }

    if ( barcodeType == "2" ) { // EAN 13
        int i;
        QString barcode;
        if (code.count() == 12) {
            int checksum = 0;
            // no 13th (checksum) number entered
            for ( i = 11; i >= 0; i-=2 ) {
                checksum = checksum + code.mid(i, 1).toInt();
            }
            checksum = checksum * 3;
            for ( i = 10; i >= 0; i-=2 ) {
                checksum = checksum + code.mid(i, 1).toInt();
            }
            code = code.append(QString::number((10 - checksum % 10) % 10));
        }
        // The first digit is taken just as it is, the second one comes from table A
        barcode = code.at(0) + static_cast<char>(65 + code.mid(1, 1).toInt());
        int first = code.mid(0, 1).toInt();
        bool tableA;
        for ( i = 2; i < 7; i+=1 ) {
            tableA = false;
            switch (i) {
                case 2:
                    switch (first) {
                        case 0: tableA = true; break;
                        case 1: tableA = true; break;
                        case 2: tableA = true; break;
                        case 3: tableA = true; break;
                    }
                    break;
                case 3:
                    switch (first) {
                        case 0: tableA = true; break;
                        case 4: tableA = true; break;
                        case 7: tableA = true; break;
                        case 8: tableA = true; break;
                    }
                    break;
                case 4:
                    switch (first) {
                        case 0: tableA = true; break;
                        case 1: tableA = true; break;
                        case 4: tableA = true; break;
                        case 5: tableA = true; break;
                        case 9: tableA = true; break;
                    }
                    break;
                case 5:
                    switch (first) {
                        case 0: tableA = true; break;
                        case 2: tableA = true; break;
                        case 5: tableA = true; break;
                        case 6: tableA = true; break;
                        case 7: tableA = true; break;
                    }
                    break;
                case 6:
                    switch (first) {
                        case 0: tableA = true; break;
                        case 3: tableA = true; break;
                        case 6: tableA = true; break;
                        case 8: tableA = true; break;
                        case 9: tableA = true; break;
                    }
                    break;
            }
            if (tableA) {
                barcode = barcode + static_cast<char>(65 + code.mid(i, 1).toInt());
            } else {
                barcode = barcode + static_cast<char>(75 + code.mid(i, 1).toInt());
            }
        }
        barcode = barcode + "*";  // Add middle separator
        for ( i = 7; i < 13; i+=1 ) {
            barcode = barcode + static_cast<char>(97 + code.mid(i, 1).toInt());
        }
        barcode = barcode + "+";  // Add end mark
        QTextStream(stdout) << "barcode = " << barcode;
        encoded = barcode;
    }
    return encoded;
}

int CodeViewModel::codeToChar(int code) {
    return code + 105;
}

int CodeViewModel::charToCode(int ch) {
    return ch - 32;
}

int CodeViewModel::calculateCheckCharacter(QString code) {
    QByteArray encapBarcode(code.toUtf8());  // Convert code to utf8

    //Calculate check character
    long long sum = CODE128_B_START; //The sum starts with the B Code start character value
    int weight = 1; //Initial weight is 1

    foreach(char ch, encapBarcode) {
        int code_char = charToCode((int)ch); //Calculate character code
        sum += code_char*weight; //add weighted code to sum
        weight++; //increment weight
    }

    int remain = sum%103;  // The check character is the modulo 103 of the sum

    //Calculate the font integer from the code integer
    if(remain >= 95)
        remain += 105;
    else
        remain += 32;

    return remain;
}

QDataStream &operator <<(QDataStream &stream, const CodeViewModel &code) {
    stream << code.m_name;
    stream << code.m_description;
    stream << code.m_code;
    stream << code.m_type;

    return stream;
}

QDataStream &operator >>(QDataStream &stream, CodeViewModel &code) {
    stream >> code.m_name;
    stream >> code.m_description;
    stream >> code.m_code;
    stream >> code.m_type;

    return stream;
}
