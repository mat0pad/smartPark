#ifndef INTERRUPT_H
#define INTERRUPT_H


class Interrupt
{
public:
    Interrupt();
    void myInterruptDisplay(void);
    void myInterruptCamera(void);
    void interruptInit(void);

private:
    bool CameraOn_ = false;
    bool DisplayOn_ = true;
    Camera *currentCamera_ = NULL;
};

#endif // INTERRUPT_H
