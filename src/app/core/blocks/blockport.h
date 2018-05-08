/**
 * Part of block editor project for ICP at FIT BUT 2017-2018.
 *
 * @package ICP-2017-2018
 * @authors Son Hai Nguyen xnguye16@stud.fit.vutbr.cz, Josef Kolář xkolar71@stud.fit.vutbr.cz
 * @date 06-05-2018
 * @version 1.0
 */

#ifndef BLOCKPORT_H
#define BLOCKPORT_H

#include <QStringList>
#include <app/core/identified.h>
#include <app/core/base.h>
#include <app/ui/blockportview.h>

/**
 * Type utility class for handling block ports.
 */
class Type {
    public:
        /**
         * Possible data types.
         */
        enum TypeE {
            Scalar,
            Vector,
            Angle
        };

        /**
         * Converts type to string.
         * @param type to convert
         * @return strng resp.
         */
        static QString toString(TypeE type);
        /**
         * Gets type from string.
         * @param str to convert
         * @return type
         */
        static TypeE fromString(const QString &str);
        /**
         * Returns regex validator for type.
         * @param type type for validator
         * @return regex string
         */
        static QString validator(TypeE type);
        /**
         * Returns stringed default value for type.
         * @param type type
         * @return default value as string
         */
        static QString defaultValue(TypeE type);
};

/**
 * Class for one port of block.
 */
class BlockPort {
    private:
        BlockPortView* m_view;
        Identifier m_blockId;
        bool m_isOutput = false;
        Type::TypeE m_type;

    protected:
        /**
         * Sets port view for core port.
         * @param v view for port
         */
        void setView(BlockPortView* v);

    public:
        BlockPort(Identifier blockId, Type::TypeE type);

        virtual ~BlockPort();
        /**
         * Returns labels of ports.
         * @return labels list
         */
        virtual QStringList labels() const = 0;
        /**
         * Returns value of port
         * @return value of port
         */
        MappedDataValues value() const;

        /**
         * Sets new value for port.
         * @param v new value
         */
        virtual void setValue(MappedDataValues v) = 0;
        /**
         * Sets flag if is port as output.
         * @param v state
         */
        virtual void setIsOutput(bool v);

        /**
         * Return view for port.
         * @return port view
         */
        BlockPortView* view() const;
        /**
         * Returns id of block for port.
         * @return identifier
         */
        Identifier blockId() const;
        /**
         * Is port output?
         * @return state
         */
        bool isOutput() const;
        /**
         * Returns type of port.
         * @return type
         */
        Type::TypeE type() const;
        /**
         * Is port valid?
         * @return state
         */
        bool valid() const;
        /**
         * Has port connection?
         * @return state
         */
        bool isConnected() const;
};

#endif // BLOCKPORT_H
