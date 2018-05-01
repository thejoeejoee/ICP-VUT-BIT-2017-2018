#ifndef BLOCKPORT_H
#define BLOCKPORT_H

#include <QStringList>
#include <app/core/identified.h>
#include <app/core/base.h>
#include <app/ui/blockportview.h>

class Type
{
    public:
        enum TypeE {
            Scalar,
            Vector,
            Angle
        };
        // TODO add validators
    static QString toString(TypeE type);
    static TypeE fromString(const QString& str);
    static QString validator(TypeE type);
    static QString defaultValue(TypeE type);
};

class BlockPort
{
    private:
        BlockPortView* m_view;
        Identifier m_blockId;
        bool m_isOutput = false;
        Type::TypeE m_type;

    protected:
        void setView(BlockPortView* v);

    public:
        BlockPort(Identifier blockId, Type::TypeE type);

        virtual ~BlockPort();
        virtual QStringList labels() const = 0;
        MappedDataValues value() const;
        virtual void setValue(MappedDataValues v) = 0;
        virtual void setIsOutput(bool v);

        BlockPortView* view() const;
        Identifier blockId() const;
        bool isOutput() const;
        Type::TypeE type() const;
};

#endif // BLOCKPORT_H
