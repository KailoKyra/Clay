        ;; AY-3-8912

AY_reset:
        ;; test

        ld      A, AY_ENABLE_REG
        out     (AY_REGISTER_LATCH), A
        ld      A, 62
        out     (AY_WRITE), A

        ld      A, AY_ENVELOPE_COARSE_TUNE_REG
        out     (AY_REGISTER_LATCH), A
        ld      A, 0
        out     (AY_WRITE), A

        ld      A, AY_ENVELOPE_SHAPE_CONTROL_REG
        out     (AY_REGISTER_LATCH), A
        ld      A, AY_ENVELOPE_SHAPE_CONTINUE  | AY_ENVELOPE_SHAPE_ALTERNATE | AY_ENVELOPE_SHAPE_HOLD; | AY_ENVELOPE_SHAPE_ATTACK
        out     (AY_WRITE), A


        ld      A, AY_CHAN_A_TONE_COARSE_REG
        out     (AY_REGISTER_LATCH), A
        ld      A, 5
        out     (AY_WRITE), A

        ld      A, AY_CHAN_A_AMPLITUDE_REG
        out     (AY_REGISTER_LATCH), A
        ld      A, (0x10 | 15) ; put 0x10  here for amplitude modulation
        out     (AY_WRITE), A

        ret
