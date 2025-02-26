#include "Hospital.h"

#include <cassert>

std::ostream& operator<<(std::ostream& s, const EventResult& r)
{
    int enumIndex = (r.type < 0 || r.type > InvalidEvent) ? InvalidEvent : r.type;
    s << "Time[" << r.timePoint << "]: ";
    switch(enumIndex)
    {
        case DoctorQueueCheck:
            s << "Doctor(" << r.patientIdOrDoctorIndex
              << ") checked the patient queue." << std::endl;
            break;
        case RegistrationQueueEntrance:
            s << "Patient(" << r.patientIdOrDoctorIndex
              << ") " << "is registering." << std::endl;
            break;
        case RegistrationEnd:
            s << "Patient(" << r.patientIdOrDoctorIndex
              << ") registeration is complete." << std::endl;
            break;
        case ExaminationEnd:
            s << "Patient(" << r.patientIdOrDoctorIndex
              << ") examination is completed." << std::endl;
            break;
        case InvalidEvent:
        default:
            s << "Invalid Event!" << std::endl;
            break;
    }

    return s;
}

int Doctor::ExamTimeOf(const Patient& patient) const
{
    // TODO: Implement
}


Hospital::Hospital(const Doctor& d0,
                   const Doctor& d1,
                   int rTime, int docTime)
    : currentTime(0)
    , registrationTime(rTime)
    , doctorCheckTime(docTime)
{
    doctors[0] = d0;
    doctors[1] = d1;
    patientsInExam[0] = NULL;
    patientsInExam[1] = NULL;

    eventQueue.InsertItem(new Event(currentTime + doctorCheckTime, DoctorQueueCheck, 0));
    eventQueue.InsertItem(new Event(currentTime + doctorCheckTime, DoctorQueueCheck, 1));
}

Hospital::~Hospital()
{
    // TODO: Implement
}

void Hospital::AddPatient(int id, int priority)
{
    // TODO: Implement
}

EventResult Hospital::DoSingleEventIteration()
{
    // TODO: Implement
    return EventResult();
}